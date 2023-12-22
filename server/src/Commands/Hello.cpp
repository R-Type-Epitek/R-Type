//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"

Network::HelloCommandHandler::HelloCommandHandler(UDPServer& server):
    server(server)
{
}

bool Network::HelloCommandHandler::isAuthorized(int clientId)
{
    return clientId == -1;
}

Response Network::HelloCommandHandler::handleCommand(Message* message)
{
    int clientId = this->server.getClients().size();
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

    Response response = this->server.createResponse(
        clientId,
        CONNECT_TO_SERVER_COMMAND,
        statusMessage,
        nullptr,
        status
    );
    std::cout << "Client " << response.header.clientId << " connected to server" << std::endl;
    return response;
}
