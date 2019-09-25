/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#define LISTENER_PORT 4444

#include <iostream>
#include "network/BoostListener.hpp"
#include "services/ServiceLocator.hpp"
#include "services/LogService.hpp"
#include "services/BoostService.hpp"
#include "services/NetworkService.hpp"
#include "services/DataBaseService.hpp"

void cleanServices()
{
    delete(ServiceLocator<LogService>::getService());
    delete(ServiceLocator<BoostService>::getService());
    delete(ServiceLocator<DataBaseService>::getService());
    delete(ServiceLocator<NetworkService<BoostListener>>::getService());
}

void initializeServices()
{
    auto *log = new LogService;
    ServiceLocator<LogService>::registerService(*log);

    auto *boost = new BoostService;
    ServiceLocator<BoostService>::registerService(*boost);

    auto *dataBase = new DataBaseService;
    ServiceLocator<DataBaseService>::registerService(*dataBase);

    auto *network = new NetworkService<BoostListener>(LISTENER_PORT);
    ServiceLocator<NetworkService<BoostListener>>::registerService(*network);
}

int main()
{
    initializeServices();

    auto logService = ServiceLocator<LogService>::getService();
    auto netService = ServiceLocator<NetworkService<BoostListener>>::getService();

    netService->accept();
    logService->writeHour("Server is now listening on port " + std::to_string(LISTENER_PORT));

    /* Block until end of logic calls fired by network events*/
    ServiceLocator<BoostService>::getService()->runContext();

    cleanServices();
    return 0;
}
