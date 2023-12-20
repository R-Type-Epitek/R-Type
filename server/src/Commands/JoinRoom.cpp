//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"

Network::JoinRoomCommandHandler::JoinRoomCommandHandler(
    Network::UDPServer& server
): server(server)
{
}

bool Network::JoinRoomCommandHandler::isAuthorized(int clientId)
{
    for (auto& client : this->server.getClients())
        if (client.getId() == clientId)
            return true;
    return false;
}

Response Network::JoinRoomCommandHandler::handleCommand(Message* message)
{
    JoinRoomData *data = (JoinRoomData *)message->data;
    std::string statusMessage = "";
    int status = RES_SUCCESS;
    std::vector<Room> rooms = this->server.getRooms();

    if (data->roomId < 0 || data->roomId >= (int)rooms.size()) {
        statusMessage = "Invalid room ID";
        status = RES_BAD_REQUEST;
    } else if (rooms[data->roomId].isFull()) {
        statusMessage = "Room is full";
        status = RES_BAD_REQUEST;
    } else {
        statusMessage = "Joined room " + std::to_string(data->roomId);
        rooms[data->roomId].addPlayer(message->header.clientId);
    }

    return this->server.createResponse(
        message->header.clientId,
        JOIN_ROOM_COMMAND,
        statusMessage,
        status
    );
}
