//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"

Network::ConnectToServerCommandHandler::ConnectToServerCommandHandler(UDPServer &server)
  : server(server)
{
}

bool Network::ConnectToServerCommandHandler::isAuthorized(int clientId)
{
  return clientId == -1;
}

std::vector<char> Network::ConnectToServerCommandHandler::handleCommand(Message *message)
{
  std::lock_guard<std::mutex> lock(this->server.roomsMutex);
  Room &room = this->server.getRooms()[0];
  room.setState(FINISHED);
  std::cout << "Room 0 state: " << room.getState() << std::endl;

  int clientId = this->server.getNextClientIdAndIncrement();
  std::string statusMessage;
  int status = RES_SUCCESS;

  if (message->header.clientId != -1) {
    statusMessage = "Client already connected";
    status = RES_BAD_REQUEST;
  } else {
    statusMessage = "User correctly connected to server";
    Network::Client client;
    client.setEndpoint(this->server.getRemoteEndpoint());
    client.setId(clientId);
    this->server.addClient(client);
  }

  return this->server.createResponseBuffer(clientId, message->header, statusMessage, nullptr, 0, status);
}
