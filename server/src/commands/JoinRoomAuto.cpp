//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"
#include <algorithm>
#include <random>
#include <chrono>

Network::JoinRoomAutoCommandHandler::JoinRoomAutoCommandHandler(Network::UDPServer &server)
  : server(server)
{
}

bool Network::JoinRoomAutoCommandHandler::isAuthorized(int clientId)
{
  auto clientOpt = this->server.getClientById(clientId);
  if (clientOpt.has_value())
    return true;
  return false;
}

std::vector<char> Network::JoinRoomAutoCommandHandler::handleCommand(Message *message)
{
  JoinRoomData data;
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

  std::vector<int> roomIndices(rooms.size());
  std::iota(roomIndices.begin(), roomIndices.end(), 0);

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(roomIndices.begin(), roomIndices.end(), std::default_random_engine(seed));

  int oldRoomId = client.getRoomId();
  if (oldRoomId != -1) {
    rooms[client.getRoomId()].removePlayer(message->header.clientId);
    statusMessage = "Left room " + std::to_string(client.getRoomId());
    if (client.getIsInGame())
      client.setIsInGame(false);
  }

  for (int index : roomIndices) {
    if (rooms[index].isFull())
      continue;
    Room &room = rooms[index];
    if (room.getId() == oldRoomId)
      continue;
    if (oldRoomId != -1)
      statusMessage += " to join room ";
    else
      statusMessage = "Joined room ";
    statusMessage += std::to_string(room.getId());
    client.setRoomId(room.getId());
    room.addPlayer(message->header.clientId);
    data.roomId = room.getId();
    break;
  }

  if (statusMessage.empty()) {
    statusMessage = "No room available";
    status = RES_BAD_REQUEST;
  }

  std::vector<char> dataToSend(sizeof(data));
  memcpy(dataToSend.data(), &data, sizeof(data));

  return this->server.createResponseBuffer(
    message->header.clientId,
    message->header,
    statusMessage,
    dataToSend.data(),
    dataToSend.size(),
    status);
}
