//
// Created by Xavier VINCENT on 12/12/2023.
//

#include "RTypeNetwork.hpp"

Network::UDPServer::UDPServer(boost::asio::io_context &io):
    socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), std::stoi(DEFAULT_PORT)))
{
    this->initServer(std::stoi(DEFAULT_PORT));
}

Network::UDPServer::UDPServer(boost::asio::io_context &io, int port):
    socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    this->initServer(port);
}

Network::UDPServer::~UDPServer()
{
    this->socket.close();

    for (auto& worker : this->workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void Network::UDPServer::initServer(int port)
{
    std::cout << "Server listening on port " << port << std::endl;
    this->initRooms(NUMBER_OF_ROOMS);
    this->startReceive();

    int num_threads = std::thread::hardware_concurrency();

    for (int i = 0; i < num_threads; ++i) {
        workers.emplace_back(&Network::UDPServer::workerFunction, this);
    }
}

void Network::UDPServer::initRooms(int count)
{
    for (int i = 0; i < count; i++) {
        Network::Room room(i, DEFAULT_ROOM_SIZE);

        this->rooms.push_back(room);
    }
    std::cout << count <<  " rooms initialized" << std::endl;
}

void Network::UDPServer::startReceive()
{
    this->socket.async_receive_from(
        boost::asio::buffer(this->recvBuffer),
        this->remoteEndpoint,
        boost::bind(
            &Network::UDPServer::handleReceive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Network::UDPServer::handleReceive(
    const boost::system::error_code &error,
    std::size_t bytesTransferred
)
{
    (void)bytesTransferred;
    if (error && error == boost::asio::error::message_size) {
        std::cout << "Error: " << error << std::endl;
        return;
    }
    
    Message *message = (Message *)boost::asio::buffer(this->recvBuffer).data();
    this->messageQueue.push(message);
}

void Network::UDPServer::sendToAll(
    const boost::asio::const_buffer &buffer
)
{
    for (auto &client : this->clients)
        this->socket.send_to(
            buffer,
            client.getEndpoint()
        );
}

void Network::UDPServer::sendToClient(
    const boost::asio::const_buffer &buffer,
    int id
)
{
    if (id < 0 || id >= (int)this->clients.size())
        throw std::runtime_error("Invalid client id");
    if (!this->socket.is_open())
        throw std::runtime_error("Socket is not open");
    this->socket.send_to(
        buffer,
        this->clients[id].getEndpoint()
    );
}

void Network::UDPServer::processMessage(
    Message *message
)
{
    if (!strcmp(message->header.command, HELLO_COMMAND))
        return this->helloCommand(message);

    if (!this->isClientConnected(message->header.clientId))
        return this->handleInvalidClient(message);

    if (!strcmp(message->header.command, UPDATE_NAME_COMMAND))
        return this->updateNameCommand(message);
    if (!strcmp(message->header.command, JOIN_ROOM_COMMAND))
        return this->joinRoomCommand(message);
    if (!strcmp(message->header.command, INPUT_COMMAND))
        return this->inputCommand(message);
    if (!strcmp(message->header.command, START_GAME_COMMAND))
        return this->startGameCommand(message);

    throw std::runtime_error("Invalid command");
}

void Network::UDPServer::workerFunction()
{
    const int width = 20;

    while (true) {
        Message *message = this->messageQueue.pop();

        std::stringstream ss;
        ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
        ss << GREEN << "Worker Thread: " << std::this_thread::get_id() << RESET << "\n";
        ss << CYAN << std::string(60, '-') << RESET << "\n";
        ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET << message->header.command << "\n";
        ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET << message->header.dataLength << "\n";
        ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET << message->header.clientId << "\n";
        ss << CYAN << std::string(60, '-') << RESET << "\n";

        std::cout << ss.str();

        this->processMessage(message);
    }
}

Response Network::UDPServer::createResponse(
    int clientId,
    const std::string& command,
    const std::string& statusMessage,
    int status = RES_SUCCESS
)
{
    Response response;

    response.header.clientId = clientId;
    strcpy(response.header.command, command.c_str());
    response.header.dataLength = 0;
    response.header.status = status;
    strcpy(response.header.statusMessage, statusMessage.c_str());
    return response;
}

void Network::UDPServer::sendResponseAndLog(const Response& response)
{
    const int width = 20;

    this->sendToClient(
        boost::asio::buffer(&response, sizeof(response)),
        response.header.clientId
    );

    std::stringstream ss;
    ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
    ss << GREEN << "Server Response: " << RESET << "\n";
    ss << CYAN << std::string(60, '-') << RESET << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET << response.header.command << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET << response.header.dataLength << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET << response.header.clientId << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Status:" << RESET << response.header.status << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Status Message:" << RESET << response.header.statusMessage << "\n";
    ss << CYAN << std::string(60, '-') << RESET << "\n";

    std::cout << ss.str();

    this->startReceive();
}

bool Network::UDPServer::isClientConnected(int clientId)
{
    for (const auto& client : this->clients)
        if (client.getId() == clientId)
            return true;
    return false;
}

void Network::UDPServer::handleInvalidClient(Message *message)
{
    int clientId = message->header.clientId;
    std::string statusMessage = clientId < 0
        ? "Invalid client ID"
        : "Client not connected. Use " HELLO_COMMAND " command to connect";
    Response response = this->createResponse(
        clientId,
        message->header.command,
        statusMessage,
        RES_UNAUTHORIZED
    );

    this->sendResponseAndLog(response);
}

void Network::UDPServer::helloCommand(Message *message)
{
    int clientId = this->clients.size();
    std::string statusMessage;
    int status = RES_SUCCESS;

    if (message->header.clientId != -1) {
        statusMessage = "Client already connected";
        status = RES_BAD_REQUEST;
    } else {
        statusMessage = "User correctly connected to server";
        Network::Client client;
        client.setEndpoint(this->remoteEndpoint);
        client.setId(clientId);
        this->clients.push_back(client);
    }

    Response response = this->createResponse(
        clientId,
        HELLO_COMMAND,
        statusMessage,
        status
    );
    sendResponseAndLog(response);
}

void Network::UDPServer::updateNameCommand(Message *message)
{
    UpdateNameData *data = (UpdateNameData *)message->data;

    this->clients[message->header.clientId].setName(data->name);

    Response response = this->createResponse(
        message->header.clientId,
        UPDATE_NAME_COMMAND,
        "Name correctly set: " + std::string(data->name)
    );
    this->sendResponseAndLog(response);
}

void Network::UDPServer::joinRoomCommand(Message *message)
{
    JoinRoomData *data = (JoinRoomData *)message->data;
    std::string statusMessage = "";
    int status = RES_SUCCESS;

    if (data->roomId < 0 || data->roomId >= (int)this->rooms.size()) {
        statusMessage = "Invalid room ID";
        status = RES_BAD_REQUEST;
    } else if (this->rooms[data->roomId].isFull()) {
        statusMessage = "Room is full";
        status = RES_BAD_REQUEST;
    } else {
        statusMessage = "Joined room " + std::to_string(data->roomId);
        this->rooms[data->roomId].addPlayer(message->header.clientId);
    }

    Response response = this->createResponse(
        message->header.clientId,
        JOIN_ROOM_COMMAND,
        statusMessage,
        status
    );
    this->sendResponseAndLog(response);
}

void Network::UDPServer::inputCommand(Message *message)
{
    InputData *data = (InputData *)message->data;

    // Update player position
    std::cout << "Player " << message->header.clientId << " pressed key: " << data->key << std::endl;

    Response response = this->createResponse(
        message->header.clientId,
        INPUT_COMMAND,
        "Get key: \"" + std::string(data->key) + "\""
    );
    this->sendResponseAndLog(response);
}

void Network::UDPServer::startGameCommand(Message *message)
{
    StartGameData *data = (StartGameData *)message->data;

    // Start game
    // Initialize the map (all the entities)
    // Initialize the players

    Response response = this->createResponse(
        message->header.clientId,
        START_GAME_COMMAND,
        "Start game (room " + std::to_string(data->roomId) + ")"
    );
    this->sendResponseAndLog(response);
}
