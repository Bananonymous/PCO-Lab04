//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

/* Editors : Léon Surbeck, Alex Berberat */

#include "locomotivebehavior.h"
#include "ctrain_handler.h"
#include "sharedstation.h"

void LocomotiveBehavior::run()
{
    //Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Ready!");

    int nbToursLoco7 = 0, nbToursLoco42 = 0;
    bool directionAvant = true;
    constexpr int nbToursAFaire42 = 1, nbToursAFaire7 = 1;

    while(!PcoThread::thisThread()->stopRequested()) {
        // Logiques implémentées selon chaque locomotive
        if (loco.numero() == 42) {
            if (directionAvant) {
                // Logique pour aller en avant
                attendre_contact(29);
                sharedSection->request(loco, loco.priority);
                attendre_contact(22);
                sharedSection->access(loco, loco.priority);

                attendre_contact(12);
                sharedSection->leave(loco);

            } else {
                // Logique pour aller en arrière
                attendre_contact(3);
                sharedSection->request(loco, loco.priority);
                attendre_contact(10);
                sharedSection->access(loco, loco.priority);

                attendre_contact(20);
                sharedSection->leave(loco);
            }

            attendre_contact(1);
            nbToursLoco42++;
            loco.afficherMessage("Loco 42: J'ai fait : " + QString::number(nbToursLoco42) + " tours");

            //Si le nombre de tours est atteint, on attend en gare
            if (nbToursLoco42 >= nbToursAFaire42) {
                nbToursLoco42 = 0; // On remet à zéro le compteur
                sharedStation.waitingAtStation(loco); // On attend en gare
                setRandomPriority(); // On redéfinit une priorité aléatoire
                directionAvant = !directionAvant; // Inversion du flag de direction
                sharedSection->togglePriorityMode(); // Inversion de la priorité après l'attente en gare
            }
        }
        // Logiques implémentées selon chaque locomotive
        else if (loco.numero() == 7) {
            if (directionAvant) {
                // Logique pour aller en avant
                attendre_contact(33);
                sharedSection->request(loco,loco.priority);

                attendre_contact(25);
                sharedSection->access(loco, loco.priority);
                diriger_aiguillage(10, DEVIE,0);
                diriger_aiguillage(13, DEVIE,0);

                attendre_contact(15);
                diriger_aiguillage(10, TOUT_DROIT,0);
                diriger_aiguillage(13, TOUT_DROIT,0);
                sharedSection->leave(loco);

            } else {
                // Logique pour aller en arrière
                attendre_contact(6);
                sharedSection->request(loco, loco.priority);
                attendre_contact(14);
                sharedSection->access(loco, loco.priority);
                diriger_aiguillage(10, DEVIE,0);
                diriger_aiguillage(13, DEVIE,0);

                attendre_contact(24);
                sharedSection->leave(loco);
                diriger_aiguillage(10, TOUT_DROIT,0);
                diriger_aiguillage(13, TOUT_DROIT,0);
            }
            attendre_contact(5);
            nbToursLoco7++;
            loco.afficherMessage("Loco 7: J'ai fait : " + QString::number(nbToursLoco7) + " tours");

            //Si le nombre de tours est atteint, on attend en gare
            if (nbToursLoco7 >= nbToursAFaire7) {
                nbToursLoco7 = 0; // Remise à zéro du compteur
                sharedStation.waitingAtStation(loco); // On attend en gare
                directionAvant = !directionAvant; // Inversion du flag de direction
                setRandomPriority(); // On redéfinit une priorité aléatoire
            }
        }
    }
}

void LocomotiveBehavior::printStartMessage()
{
    qDebug() << "[START] Thread de la loco" << loco.numero() << "lancé";
    loco.afficherMessage("Je suis lancée !");
}

void LocomotiveBehavior::printCompletionMessage()
{
    qDebug() << "[STOP] Thread de la loco" << loco.numero() << "a terminé correctement";
    loco.afficherMessage("J'ai terminé");
}

