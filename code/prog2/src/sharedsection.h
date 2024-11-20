//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//                                         //


#ifndef SHAREDSECTION_H
#define SHAREDSECTION_H

#include <QDebug>

#include <pcosynchro/pcosemaphore.h>

#include "locomotive.h"
#include "ctrain_handler.h"
#include "sharedsectioninterface.h"

/**
 * @brief La classe SharedSection implémente l'interface SharedSectionInterface qui
 * propose les méthodes liées à la section partagée.
 */
class SharedSection final : public SharedSectionInterface {
public:
    /**
     * @brief SharedSection Constructeur de la classe qui représente la section partagée.
     * Initialisez vos éventuels attributs ici, sémaphores etc.
     */
    SharedSection() {
        // TODO
        section_semaphore.release();
        section_mutex.release();
        isUsed = false;
    }

    /**
     * @brief request Méthode a appeler pour indiquer que la locomotive désire accéder à la
     * section partagée (deux contacts avant la section partagée).
     * @param loco La locomotive qui désire accéder
     * @param locoId L'identidiant de la locomotive qui fait l'appel
     * @param entryPoint Le point d'entree de la locomotive qui fait l'appel
     */
    void request(Locomotive &loco, int priority) override {
        section_mutex.acquire();
        waitingLocos.push_back(&loco); // Ajouter la locomotive à la liste d'attente
        loco.afficherMessage("Requête déposée avec priorité " + QString::number(priority));
        section_mutex.release();
    }

    /**
     * @brief getAccess Méthode à appeler pour accéder à la section partagée, doit arrêter la
     * locomotive et mettre son thread en attente si la section est occupée ou va être occupée
     * par une locomotive de plus haute priorité. Si la locomotive et son thread ont été mis en
     * attente, le thread doit être reveillé lorsque la section partagée est à nouveau libre et
     * la locomotive redémarée. (méthode à appeler un contact avant la section partagée).
     * @param loco La locomotive qui essaie accéder à la section partagée
     * @param locoId L'identidiant de la locomotive qui fait l'appel
     */
    void access(Locomotive &loco, int priority) override {
        while (true) {
            section_mutex.acquire();

            // Vérifier si la locomotive courante a la plus haute priorité
            Locomotive *highestPriorityLoco = getHighestPriorityLoco();
            if (highestPriorityLoco == &loco && !isUsed) {
                // La locomotive courante a la priorité et le tronçon est libre
                loco.demarrer();
                isUsed = true;
                waitingLocos.erase(
                    std::remove(waitingLocos.begin(), waitingLocos.end(), &loco),
                    waitingLocos.end()
                );
                section_mutex.release();
                loco.afficherMessage("Accès accordé avec priorité " + QString::number(priority));
                section_semaphore.acquire(); // Acquérir le tronçon
                break;
            } else {
                loco.arreter();
            }

            section_mutex.release();
        }
    }

    /**
     * @brief leave Méthode à appeler pour indiquer que la locomotive est sortie de la section
     * partagée. (reveille les threads des locomotives potentiellement en attente).
     * @param loco La locomotive qui quitte la section partagée
     * @param locoId L'identidiant de la locomotive qui fait l'appel
     */
    void leave(Locomotive &loco) override {
        section_mutex.acquire();
        isUsed = false; // Libérer le tronçon
        section_semaphore.release(); // Libérer l'accès
        loco.afficherMessage("Tronçon libéré par loco " + QString::number(loco.numero()));
        section_mutex.release();
    }

    void togglePriorityMode() override {
        priorityMode = (priorityMode == PriorityMode::HIGH_PRIORITY)
                           ? PriorityMode::LOW_PRIORITY
                           : PriorityMode::HIGH_PRIORITY;
    }

private:
    /* A vous d'ajouter ce qu'il vous faut */
    struct ComparePriority {
        bool operator()(const Locomotive *l1, const Locomotive *l2) {
            return l1->priority < l2->priority; // Priorité décroissante
        }
    };

    Locomotive *getHighestPriorityLoco() {
        if (waitingLocos.empty()) return nullptr;
        if (priorityMode == PriorityMode::HIGH_PRIORITY) {
            return *std::max_element(waitingLocos.begin(), waitingLocos.end(),
                                     [this](Locomotive *l1, Locomotive *l2) {
                                         return l1->priority < l2->priority;
                                     });
        }

        return *std::min_element(waitingLocos.begin(), waitingLocos.end(),
                                 [this](Locomotive *l1, Locomotive *l2) {
                                     return l1->priority < l2->priority;
                                 });
    }

    // Méthodes privées ...
    // Attributes privés ...
    bool isUsed = false;
    PcoSemaphore section_semaphore;
    PcoSemaphore section_mutex;
    std::vector<Locomotive *> waitingLocos;
    PriorityMode priorityMode = PriorityMode::HIGH_PRIORITY;
};


#endif // SHAREDSECTION_H
