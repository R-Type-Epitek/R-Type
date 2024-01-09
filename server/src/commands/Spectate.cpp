//
// Created by Xavier VINCENT on 09/01/2023.
//

#include "RTypeNetwork.hpp"

Network::SpectateCommandHandler::SpectateCommandHandler(Network::UDPServer &server)
  : server(server)
{
}

bool Network::SpectateCommandHandler::isAuthorized(int clientId)
{
  auto clientOpt = this->server.getClientById(clientId);
  if (clientOpt.has_value())
    return true;
  return false;
}

std::vector<char> Network::SpectateCommandHandler::handleCommand(Message *message)
{
  SpectateData *data = (SpectateData *)message->data;
  std::string statusMessage;
  int status = RES_SUCCESS;

  Room &room = this->server.getRooms()[data->roomId];
  auto clientOpt = this->server.getClientById(message->header.clientId);
  if (clientOpt.has_value() == false)
    return this->server.createResponseBuffer(
      message->header.clientId,
      message->header,
      "Client not found",
      nullptr,
      0,
      RES_UNAUTHORIZED);
  Client &client = clientOpt.value();

  enum RoomState const state = room.getState();
  if (state != RUNNING) {
    status = RES_UNAUTHORIZED;
    statusMessage = "Room is not running";
  } else {
    if (client.getIsInGame()) {
      status = RES_UNAUTHORIZED;
      statusMessage = "Client is already in game";
    } else if (client.getIsSpectator()) {
      status = RES_UNAUTHORIZED;
      statusMessage = "Client is already a spectator";
    } else {
      client.setIsInGame(true);
      client.setIsSpectator(true);
      statusMessage = "Client is spectating room " + std::to_string(data->roomId);
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
