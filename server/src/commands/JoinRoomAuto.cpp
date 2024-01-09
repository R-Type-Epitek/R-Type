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
  for (auto &client : this->server.getClients())
    if (client.getId() == clientId)
      return true;
  return false;
}

std::vector<char> Network::JoinRoomAutoCommandHandler::handleCommand(Message *message)
{
  JoinRoomData data;
  std::string statusMessage;
  int status = RES_SUCCESS;
  std::vector<Room> &rooms = this->server.getRooms();

  std::vector<int> roomIndices(rooms.size());
  std::iota(roomIndices.begin(), roomIndices.end(), 0);

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(roomIndices.begin(), roomIndices.end(), std::default_random_engine(seed));

  for (int index : roomIndices) {
    if (rooms[index].isFull())
      continue;
    Room &room = rooms[index];
    statusMessage = "Joined room " + std::to_string(room.getId());
    this->server.getClients()[message->header.clientId].setRoomId(room.getId());
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
