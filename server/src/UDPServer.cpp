//
// Created by Xavier VINCENT on 12/12/2023.
//

#include "RTypeNetwork.hpp"

Network::UDPServer::UDPServer(boost::asio::io_context &io):
    socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), std::stoi(DEFAULT_PORT))),
    clientsConnectionTimer(io)
{
    this->initServer(std::stoi(DEFAULT_PORT));
}

Network::UDPServer::UDPServer(boost::asio::io_context &io, int port):
    socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
    clientsConnectionTimer(io)
{
    this->initServer(port);
}

Network::UDPServer::~UDPServer()
{
    this->socket.close();
    this->clientsConnectionTimer.cancel();

    for (auto& worker : this->workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

boost::asio::ip::udp::socket& Network::UDPServer::getSocket()
{
    return this->socket;
}

std::vector<Network::Client>& Network::UDPServer::getClients()
{
    return this->clients;
}

boost::array<char, 1024> Network::UDPServer::getRecvBuffer() const
{
    return this->recvBuffer;
}

boost::asio::ip::udp::endpoint Network::UDPServer::getRemoteEndpoint() const
{
    return this->remoteEndpoint;
}

std::vector<Network::Room>& Network::UDPServer::getRooms()
{
    return this->rooms;
}

void Network::UDPServer::addClient(Network::Client client)
{
    this->clients.push_back(client);
}

void Network::UDPServer::initServer(int port)
{
    std::cout << "Server listening on port " << port << std::endl;
    this->initRooms(NUMBER_OF_ROOMS);
    this->registerCommandHandlers();
    this->startReceive();
    this->startCheckClientsConnectionTimer();

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

    char *data = this->recvBuffer.data();
    MessageType* type = (MessageType*)data;

    switch (*type) {
        case MessageType::Response:
            return this->processResponse((Response *)data);
            break;
        case MessageType::Message:
            return this->messageQueue.push((TimedMessage){
                (Message *)data,
                std::chrono::high_resolution_clock::now()
            });
        default:
            throw std::runtime_error("Invalid message type");
    }
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

void Network::UDPServer::sendToAllClientsInRoom(
    const boost::asio::const_buffer &buffer,
    int roomId
)
{
    if (roomId < 0 || roomId >= (int)this->rooms.size())
        throw std::runtime_error("Invalid room id: " + std::to_string(roomId));
    for (auto &clientId : this->rooms[roomId].getPlayers())
        this->socket.send_to(
            buffer,
            this->clients[clientId].getEndpoint()
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
    TimedMessage timedMessage
)
{
    Message *message = timedMessage.message;

    auto it = this->commandHandlers.find(message->header.command);
    if (it != this->commandHandlers.end()) {
        if (!it->second->isAuthorized(message->header.clientId))
            return this->handleInvalidClient(timedMessage);
        Response response = it->second->handleCommand(message);
        this->sendResponseAndLog(timedMessage, response);
    } else {
        return this->handleInvalidCommand(timedMessage);
    }
}

void Network::UDPServer::processResponse(Response *response)
{
    const int width = 20;

    std::stringstream ss;
    ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
    ss << GREEN << "Worker Thread: " << std::this_thread::get_id() << RESET << "\n";
    ss << CYAN << std::string(60, '-') << RESET << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET << response->header.command << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET << response->header.dataLength << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET << response->header.clientId << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Status:" << RESET << response->header.status << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Status Message:" << RESET << response->header.statusMessage << "\n";
    ss << CYAN << std::string(60, '-') << RESET << "\n";
    std::cout << ss.str();

    if (!strcmp(response->header.command, SERVER_COMMAND_CHECK_CONNECTION)) {
        if (response->header.status == RES_SUCCESS) {
            std::cout << "Client " << response->header.clientId << " is connected" << std::endl;
        } else {
            std::cout << "Client " << response->header.clientId << " is not connected" << std::endl;
        }
    }
    std::cout << "Unknown command: " << response->header.command << std::endl;
}

void Network::UDPServer::workerFunction()
{
    const int width = 20;

    while (true) {
        TimedMessage timedMessage = this->messageQueue.pop();
        Message *message = timedMessage.message;

        std::stringstream ss;
        ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
        ss << GREEN << "Worker Thread: " << std::this_thread::get_id() << RESET << "\n";
        ss << CYAN << std::string(60, '-') << RESET << "\n";
        ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET << message->header.command << "\n";
        ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET << message->header.dataLength << "\n";
        ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET << message->header.clientId << "\n";
        ss << CYAN << std::string(60, '-') << RESET << "\n";
        std::cout << ss.str();

        this->processMessage(timedMessage);
    }
}

Response Network::UDPServer::createResponse(
    int clientId,
    const std::string& command,
    const std::string& statusMessage,
    const char data[],
    int dataSize,
    int status
)
{
    MessageType type = MessageType::Response;

    ResponseHeader header;
    header.clientId = clientId;
    strcpy(header.command, command.c_str());
    header.dataLength = dataSize;
    header.status = status;
    strcpy(header.statusMessage, statusMessage.c_str());

    size_t totalSize = sizeof(type) + sizeof(header) + dataSize;
    std::vector<char> messageBuffer(totalSize);

    memcpy(messageBuffer.data(), &type, sizeof(type));
    memcpy(messageBuffer.data() + sizeof(type), &header, sizeof(header));
    if (data != nullptr)
        memcpy(messageBuffer.data() + sizeof(type) + sizeof(header), data, dataSize);

    Response *response = (Response *)messageBuffer.data();

    return *response;
}

void Network::UDPServer::sendResponseAndLog(
    TimedMessage timedMessage,
    const Response& response
)
{
    const int width = 20;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - timedMessage.timestamp).count();

    this->sendToClient(
        boost::asio::buffer(&response, sizeof(response)),
        response.header.clientId
    );

    std::stringstream ss;
    ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
    ss << GREEN << "Response: " << RESET << "\n";
    ss << CYAN << std::string(60, '-') << RESET << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET << response.header.command << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET << response.header.dataLength << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET << response.header.clientId << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Status:" << RESET << response.header.status << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Status Message:" << RESET << response.header.statusMessage << "\n";
    ss << YELLOW << std::left << std::setw(width) << "Duration:" << RESET << duration << "ms\n";
    ss << CYAN << std::string(60, '-') << RESET << "\n";

    std::cout << ss.str();

    this->startReceive();
}

bool Network::UDPServer::isClientRegistered(int clientId)
{
    for (const auto& client : this->clients)
        if (client.getId() == clientId)
            return true;
    return false;
}

bool Network::UDPServer::isClientConnected(int clientId)
{
    Message message = {
        .header = {
            .clientId = clientId,
            .command = SERVER_COMMAND_CHECK_CONNECTION,
            .dataLength = 0
        }
    };

    this->sendToClient(
        boost::asio::buffer(&message, sizeof(message)),
        clientId
    );

    return false;
}

void Network::UDPServer::startCheckClientsConnectionTimer()
{
    this->clientsConnectionTimer.expires_from_now(std::chrono::seconds(2));
    this->clientsConnectionTimer.async_wait([this](const boost::system::error_code& error) {
        if (!error) {
            this->checkClients();
            this->startCheckClientsConnectionTimer();
        }
    });
}

void Network::UDPServer::checkClients()
{
    for (auto it = clients.begin(); it != clients.end();) {
        if (it->getRoomId() != -1 && !this->isClientConnected(it->getId())) {
            ServerClientDisconnectedData data = {
                .clientId = it->getId()
            };
            MessageHeader header = {
                .clientId = it->getId(),
                .command = SERVER_COMMAND_CHECK_CONNECTION,
                .dataLength = sizeof(data)
            };
            std::vector<char> messageBuffer(sizeof(header) + sizeof(data));

            memcpy(messageBuffer.data(), &header, sizeof(header));
            memcpy(messageBuffer.data() + sizeof(header), &data, sizeof(data));
            this->sendToAllClientsInRoom(
                boost::asio::buffer(messageBuffer.data(), messageBuffer.size()),
                it->getRoomId()
            );
            it = this->clients.erase(it);
        } else {
            ++it;
        }
    }
}

void Network::UDPServer::registerCommandHandlers()
{
    this->commandHandlers[CONNECT_TO_SERVER_COMMAND] = std::make_unique<HelloCommandHandler>(*this);
    this->commandHandlers[UPDATE_NAME_COMMAND] = std::make_unique<UpdateNameCommandHandler>(*this);
    this->commandHandlers[JOIN_ROOM_COMMAND] = std::make_unique<JoinRoomCommandHandler>(*this);
    this->commandHandlers[INPUT_COMMAND] = std::make_unique<InputCommandHandler>(*this);
    this->commandHandlers[START_GAME_COMMAND] = std::make_unique<StartGameCommandHandler>(*this);
}

void Network::UDPServer::handleInvalidClient(TimedMessage timedMessage)
{
    int clientId = timedMessage.message->header.clientId;
    std::string statusMessage = clientId < 0
        ? "Invalid client ID"
        : "Client not connected. Use " CONNECT_TO_SERVER_COMMAND " command to connect";

    Response response = this->createResponse(
        clientId,
        timedMessage.message->header.command,
        statusMessage,
        nullptr,
        0,
        RES_UNAUTHORIZED
    );

    return this->sendResponseAndLog(timedMessage, response);
}

void Network::UDPServer::handleInvalidCommand(TimedMessage timedMessage)
{
    Response response = this->createResponse(
        timedMessage.message->header.clientId,
        timedMessage.message->header.command,
        "Invalid command",
        nullptr,
        0,
        RES_BAD_REQUEST
    );

    return this->sendResponseAndLog(timedMessage, response);
}
