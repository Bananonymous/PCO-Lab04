//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

/* Editors : Léon Surbeck, Alex Berberat */

#include <chrono>
#include <thread>

#include "sharedstation.h"

SharedStation::SharedStation(int nbTrains): totLocos(nbTrains), waiting_at_station_semaphore(0), goingToStation(1) {
    waitingLocos = false;
}


void SharedStation::waitingAtStation(Locomotive& loco)
{
    loco.arreter();
    loco.inverserSens();
    loco.afficherMessage("Loco " + QString::number(loco.numero()) + " inversée, attend en gare...");

    goingToStation.acquire();
    if (waitingLocos >= totLocos - 1) {
        // Si une assez d'autres locomotives sont déjà en attente, libère ces locomotives après 3 secondes
        loco.afficherMessage("Au moins une loco est déjà en gare");
        goingToStation.release();
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Temps d'attente pour passagers
        for(int i = 0; i < waitingLocos; ++i) {
            waiting_at_station_semaphore.release(); // Libération des locomotives en attente
        }
        waitingLocos = 0;
    } else {
        // Première locomotive arrivée, elle attend la seconde
        loco.afficherMessage("Je suis la première");
        ++waitingLocos;
        goingToStation.release();
        waiting_at_station_semaphore.acquire(); // Attente de libération par la seconde locomotive
    }

    loco.demarrer();
    loco.afficherMessage("Je repars !");
}
