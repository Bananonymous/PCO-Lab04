
/* Editors : Léon Surbeck, Alex Berberat */

#ifndef SHARED_STATION_H
#define SHARED_STATION_H

#include <pcosynchro/pcosemaphore.h>
#include "locomotive.h"


/**
 * @brief La classe SharedStation représente une gare partagée par plusieurs locomotives
 */
class SharedStation
{
public:
    /**
     * @brief SharedStation Constructeur de la classe SharedStation
     * @param nbTrains Le nombre de locomotives qui vont passer par la gare
     */
    SharedStation(int nbTrains);

    /**
     * @brief waitingAtStation Méthode à appeler par une locomotive pour attendre en gare
     * avec gestion de l'attente passive de la seconde locomotive.
     * @param loco La locomotive qui attend en gare
     */
    void waitingAtStation(Locomotive& loco);

private:
    int waitingLocos, totLocos;
    PcoSemaphore waiting_at_station_semaphore;
    PcoSemaphore goingToStation;
};

#endif // SHARED_STATION_H
