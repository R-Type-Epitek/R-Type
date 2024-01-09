//
// Created by Xavier VINCENT on 09/01/2024.
//

#include "RTypeNetwork.hpp"

Network::KickPlayerCommandHandler::KickPlayerCommandHandler(Network::UDPServer &server)
  : server(server)
{
}

bool Network::KickPlayerCommandHandler::isAuthorized(int clientId)
{
  for (auto &client : this->server.getClients())
    if (client.getId() == clientId)
      return true;
  return false;
}

std::vector<char> Network::KickPlayerCommandHandler::handleCommand(Message *message)
{
  KickPlayerData *data = (KickPlayerData *)message->data;
  std::string statusMessage;
  int status = RES_SUCCESS;

  bool found = false;
  for (auto &client : this->server.getClients())
    if (client.getId() == data->clientId)
      found = true;

  if (!found) {
    status = RES_UNAUTHORIZED;
    statusMessage = "Player not found";
  } else {
    Client &client = this->server.getClientById(data->clientId);
    if (client.getRoomId() != data->clientId) {
      status = RES_UNAUTHORIZED;
      statusMessage = "Player not in the same room";
    } else {
      this->server.notifyAndRemoveClient(client.getId());
      statusMessage = "Player " + std::to_string(client.getId()) + " kicked";
    }
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
