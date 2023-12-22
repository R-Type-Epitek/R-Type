//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"

Network::StartGameCommandHandler::StartGameCommandHandler(
    Network::UDPServer& server
): server(server)
{
}

bool Network::StartGameCommandHandler::isAuthorized(int clientId)
{
    for (auto& client : this->server.getClients())
        if (client.getId() == clientId)
            return true;
    return false;
}

Response Network::StartGameCommandHandler::handleCommand(Message* message)
{
    StartGameData *data = (StartGameData *)message->data;

    // Start game
    // Initialize the map (all the entities)
    // Initialize the players

    std::vector<char> dataToSend(sizeof(*data));
    memcpy(dataToSend.data(), data, sizeof(*data));

    return this->server.createResponse(
        message->header.clientId,
        START_GAME_COMMAND,
        "Start game (room " + std::to_string(data->roomId) + ")",
        dataToSend.data()
    );
}
