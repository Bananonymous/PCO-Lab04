/* Editors : Léon Surbeck, Alex Berberat */

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
     * Initialisation des attributs.
     */
    SharedSection() : section_mutex(1), section_waiting_locos(0) {
        isUsed = false;
    }

    /**
     * @brief request Méthode a appeler pour indiquer que la locomotive désire accéder à la
     * section partagée (deux contacts avant la section partagée).
     * @param loco La locomotive qui désire accéder
     * @param priority La priorité de la locomotive qui fait l'appel
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
     * @param priority La priorité de la locomotive qui fait l'appel
     */
    void access(Locomotive &loco, int priority) override {
        section_mutex.acquire();

        // Vérifier si la locomotive courante a la plus haute priorité
        Locomotive *highestPriorityLoco = getHighestPriorityLoco();
        if (highestPriorityLoco == &loco && !isUsed) {
            // La locomotive courante a la priorité et le tronçon est libre
            isUsed = true;
            waitingLocos.erase(
                std::remove(waitingLocos.begin(), waitingLocos.end(), &loco),
                waitingLocos.end()
            );
            loco.afficherMessage("Accès accordé avec priorité " + QString::number(priority));
            section_mutex.release();
        } else {
            loco.afficherMessage("Attente, section occupée");
            loco.arreter();
            section_mutex.release();
            section_waiting_locos.acquire();
            section_mutex.acquire();
            waitingLocos.erase(
                std::remove(waitingLocos.begin(), waitingLocos.end(), &loco),
                waitingLocos.end()
            );
            loco.afficherMessage("Accès accordé avec priorité " + QString::number(priority));
            loco.demarrer();
            section_mutex.release();
        }
    }

    /**
     * @brief leave Méthode à appeler pour indiquer que la locomotive est sortie de la section
     * partagée. (reveille les threads des locomotives potentiellement en attente).
     * @param loco La locomotive qui quitte la section partagée
     */
    void leave(Locomotive &loco) override {
        section_mutex.acquire();
        isUsed = false; // Libérer le tronçon
        loco.afficherMessage("Tronçon libéré par loco " + QString::number(loco.numero()));

        if (!waitingLocos.empty()) {
            section_waiting_locos.release(); // Libérer l'accès seulement si des locomotives attendent pour éviter les multiples libérations
        }

        section_mutex.release();
    }

    void togglePriorityMode() override {
        priorityMode = (priorityMode == PriorityMode::HIGH_PRIORITY)
                           ? PriorityMode::LOW_PRIORITY
                           : PriorityMode::HIGH_PRIORITY;
    }

private:
    Locomotive *getHighestPriorityLoco() {
        if (waitingLocos.empty()) return nullptr;

        Locomotive *selectedLoco = nullptr;

        for (const auto loco : waitingLocos) {
            if (selectedLoco == nullptr) {
                selectedLoco = loco;
            } else {
                if (priorityMode == PriorityMode::HIGH_PRIORITY) {
                    // En mode HIGH_PRIORITY, on choisit la locomotive avec la priorité la plus élevée
                    if (loco->priority > selectedLoco->priority ||
                        (loco->priority == selectedLoco->priority && loco == waitingLocos.front())) {
                        selectedLoco = loco;
                        }
                } else if (priorityMode == PriorityMode::LOW_PRIORITY) {
                    // En mode LOW_PRIORITY, on choisit la locomotive avec la priorité la plus basse
                    if (loco->priority < selectedLoco->priority ||
                        (loco->priority == selectedLoco->priority && loco == waitingLocos.front())) {
                        selectedLoco = loco;
                        }
                }
            }
        }

        return selectedLoco;
    }

    bool isUsed = false;
    PcoSemaphore section_waiting_locos;
    PcoSemaphore section_mutex;
    std::vector<Locomotive *> waitingLocos;
    PriorityMode priorityMode = PriorityMode::HIGH_PRIORITY;
};

#endif // SHAREDSECTION_H
