//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"

Network::JoinRoomCommandHandler::JoinRoomCommandHandler(Network::UDPServer &server)
  : server(server)
{
}

bool Network::JoinRoomCommandHandler::isAuthorized(int clientId)
{
  auto clientOpt = this->server.getClientById(clientId);
  if (clientOpt.has_value())
    return true;
  return false;
}

std::vector<char> Network::JoinRoomCommandHandler::handleCommand(Message *message)
{
  JoinRoomData *data = (JoinRoomData *)message->data;
  std::string statusMessage;
  int status = RES_SUCCESS;
  std::vector<Room> &rooms = this->server.getRooms();

  auto clientOpt = this->server.getClientById(message->header.clientId);
  if (!clientOpt.has_value())
    return this->server.createResponseBuffer(
      message->header.clientId,
      message->header,
      "Client not found",
      nullptr,
      0,
      RES_BAD_REQUEST);

  Client &client = clientOpt.value();

  if (data->roomId < 0 || data->roomId >= (int)rooms.size()) {
    statusMessage = "Invalid room ID";
    status = RES_BAD_REQUEST;
  } else if (rooms[data->roomId].isFull()) {
    statusMessage = "Room is full";
    status = RES_BAD_REQUEST;
  } else {
    int oldRoomId = client.getRoomId();
    if (oldRoomId != -1) {
      rooms[oldRoomId].removePlayer(message->header.clientId);
      statusMessage =
        "Left room " + std::to_string(oldRoomId) + " to join room " + std::to_string(data->roomId);
      if (client.getIsInGame())
        client.setIsInGame(false);
    } else {
      statusMessage = "Joined room " + std::to_string(data->roomId);
    }
    client.setRoomId(data->roomId);
    rooms[data->roomId].addPlayer(message->header.clientId);
  }
  std::vector<char> dataToSend(sizeof(*data));
  memcpy(dataToSend.data(), data, sizeof(*data));

  return this->server.createResponseBuffer(
    message->header.clientId,
    message->header,
    statusMessage,
    dataToSend.data(),
    dataToSend.size(),
    status);
}
