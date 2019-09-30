/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include <iostream>
#include "database/SqliteProvider.hpp"
#include "network/BoostListener.hpp"
#include "services/ServiceLocator.hpp"
#include "services/LogService.hpp"
#include "services/BoostService.hpp"
#include "services/NetworkService.hpp"
#include "services/DataBaseService.hpp"
#include "services/DispatchService.hpp"
#include "services/DispatchService.hpp"
#include "services/ClientService.hpp"

int main()
{
    auto logService = ServiceLocator<LogService>::getService();
    auto netService = ServiceLocator<NetworkService<BoostListener>>::getService();
    auto dbService = ServiceLocator<DataBaseService<SqliteProvider>>::getService();
    auto boostService = ServiceLocator<BoostService>::getService();

    /* Open default database (DATABASE_DEFAULT_NAME) */
    if (dbService->openDataBase()) {
        logService->writeHour("Database opened");
    } else {
        logService->writeError("Unable to open database ' " + std::string(DATABASE_DEFAULT_NAME) + "'");
    }

    netService->accept();
    logService->writeHour("Server is now listening on port " + std::to_string(LISTENER_DEFAULT_PORT));

    /* set first client id to 0 */
    Client::ReferenceId = 0;

    /* Block until end of logic calls fired by network events*/
    boostService->runContext();

    /* When there is nothing to do, close listener. */
    netService->stop();
    return 0;
}
