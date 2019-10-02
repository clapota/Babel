/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include <iostream>
#include <IO/NativeBinaryWriter.hpp>
#include <IO/NativeBinaryReader.hpp>
#include <Packets/AcceptFriendPacket.hpp>
#include "database/SqliteProvider.hpp"
#include "network/BoostListener.hpp"
#include "services/ServiceLocator.hpp"
#include "services/LogService.hpp"
#include "services/BoostService.hpp"
#include "services/NetworkService.hpp"
#include "services/DataBaseService.hpp"
#include "services/DispatchService.hpp"
#include "services/UserService.hpp"
#include "database/RequestBuilder.hpp"

int Client::ReferenceId = 0;

void exceptedClose(int s)
{
    std::cout << std::endl;
    auto logService = ServiceLocator<LogService>::getService();
    auto dbService = ServiceLocator<DataBaseService<SqliteProvider>>::getService();
    auto boostService = ServiceLocator<BoostService>::getService();
    auto netService = ServiceLocator<NetworkService<BoostListener>>::getService();

    logService->writeHour("Closing database");
    dbService->closeDataBase();
    logService->writeHour("Stopping boost context");
    boostService->stopContext();
    logService->writeHour("Stopping network listener");
    netService->stop();
    exit(0);
}

#ifdef __linux__
void handleSigInt()
{
    struct sigaction sigIntHandler{};

    sigIntHandler.sa_handler = exceptedClose;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);
};
#endif

int main()
{
    uint32_t a = 69;
    std::string bite = "test";

    NativeBinaryWriter writer;
    AcceptFriendPacket afp;

    afp.setUsername("caca1");
    afp.setAccepted(true);
    afp.serialize(writer);

    std::stringstream stream;
    stream <<  writer.Data().rdbuf()->str();

    NativeBinaryReader reader;
    AcceptFriendPacket afp2;

    reader.setStream(&stream);
    afp2.deserialize(reader);

    auto logService = ServiceLocator<LogService>::getService();
    auto netService = ServiceLocator<NetworkService<BoostListener>>::getService();
    auto dbService = ServiceLocator<DataBaseService<SqliteProvider>>::getService();
    auto boostService = ServiceLocator<BoostService>::getService();

    /* Open default database (DATABASE_DEFAULT_NAME) */
    if (dbService->openDataBase()) {
        logService->writeHour("Database opened");
        dbService->executeRequest(RequestBuilder::createRelationTable());
        dbService->executeRequest(RequestBuilder::createUserTable());
        dbService->executeRequest(RequestBuilder::addUser("toto", "SUCEMESBOULEEEES"));
    } else {
        logService->writeError("Unable to open database ' " + std::string(DATABASE_DEFAULT_NAME) + "'");
    }

    netService->accept();
    logService->writeHour("Server is now listening on port " + std::to_string(LISTENER_DEFAULT_PORT));

#ifdef __linux__
	/* Handle user interaction */
    handleSigInt();
#endif

    /* Block until end of logic calls fired by network events*/
    boostService->runContext();

    /* When there is nothing to do, close listener. */
    netService->stop();
    return 0;
}
