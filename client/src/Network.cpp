//
// Created by Xavier VINCENT on 14/12/2023.
//

#include "RTypeClient.hpp"

Client::Network::Network(
    std::string ip,
    std::string port
): socket(io)
{
    boost::asio::ip::udp::resolver resolver(this->io);
    this->remoteEndpoint = *resolver.resolve(
        boost::asio::ip::udp::v4(),
        ip,
        port
    ).begin();
    this->socket.open(boost::asio::ip::udp::v4());
    this->clientId = -1;
    this->startReceive();
    this->io.run();
}

Client::Network::~Network()
{
    this->socket.close();

    if (this->receiveThread.joinable())
        this->receiveThread.join();
}

void Client::Network::send(
  const boost::asio::const_buffer &buffer
)
{
    this->socket.send_to(
        buffer,
        this->remoteEndpoint
    );
}

void Client::Network::sendMessage(
    const std::string& command,
    const char* data
)
{
    MessageType type = MessageType::Message;

    MessageHeader header;
    header.clientId = this->clientId;
    strcpy(header.command, command.c_str());
    header.dataLength = sizeof(data);

    size_t totalSize = sizeof(type) + sizeof(header) + sizeof(data);
    std::vector<char> messageBuffer(totalSize);

    memcpy(messageBuffer.data(), &type, sizeof(type));
    memcpy(messageBuffer.data() + sizeof(type), &header, sizeof(header));
    if (data != nullptr)
        memcpy(messageBuffer.data() + sizeof(type) + sizeof(header), data, sizeof(data));

    this->send(boost::asio::buffer(messageBuffer.data(), messageBuffer.size()));
}

Response Client::Network::createResponse(
    const std::string& command,
    const std::string& statusMessage,
    const char* data,
    int status
)
{
    ResponseHeader header;
    header.clientId = this->clientId;
    strcpy(header.command, command.c_str());
    header.dataLength = sizeof(data);
    header.status = status;
    strcpy(header.statusMessage, statusMessage.c_str());

    Response response;
    response.header = header;
    if (data != nullptr)
        memcpy(response.data, data, sizeof(data));

    return response;
}

void Client::Network::sendResponse(
    const Response& response
)
{
    MessageType type = MessageType::Response;

    size_t totalSize = sizeof(type) + sizeof(Response);
    std::vector<char> messageBuffer(totalSize);

    memcpy(messageBuffer.data(), &type, sizeof(type));
    memcpy(messageBuffer.data() + sizeof(type), &response, sizeof(response));

    this->send(boost::asio::buffer(messageBuffer.data(), messageBuffer.size()));
}

void Client::Network::startReceive()
{
    this->receiveThread = std::thread([this](){
        while (true) {
            this->io.reset();
            this->socket.async_receive_from(
                boost::asio::buffer(this->recvBuffer),
                this->remoteEndpoint,
                boost::bind(
                    &Client::Network::onReceive,
                    this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                )
            );

            this->io.run();
        }
    });
}

void Client::Network::onReceive(
    const boost::system::error_code& error,
    std::size_t bytesTransferred
)
{
    (void)bytesTransferred;
    if (error && error == boost::asio::error::message_size) {
        std::cout << "Error: " << error << std::endl;
        return;
    }

    MessageType* type = (MessageType*)this->recvBuffer.data();

    switch (*type) {
        case MessageType::Response:
            return this->onServerResponse((Response*)this->recvBuffer.data());
        case MessageType::Message:
            return this->onServerMessage((Message*)this->recvBuffer.data());
        default:
            throw std::runtime_error("Invalid message type");
    }
}

void Client::Network::onServerResponse(Response* response)
{
    switch (response->header.status) {
        case RES_SUCCESS:
            break;
        case RES_BAD_REQUEST:
        case RES_UNAUTHORIZED:
        case RES_NOT_FOUND:
        case RES_INTERNAL_ERROR:
            throw std::runtime_error(response->header.statusMessage);
        default:
            throw std::runtime_error("Invalid response status: " + std::to_string(response->header.status));
    }

    if (!strcmp(response->header.command, CONNECT_TO_SERVER_COMMAND))
        return this->onConnectToServerResponse(response);
    else if (!strcmp(response->header.command, UPDATE_NAME_COMMAND))
        return this->onUpdateNameResponse(response);
    else if (!strcmp(response->header.command, JOIN_ROOM_COMMAND))
        return this->onJoinRoomResponse(response);
    else if (!strcmp(response->header.command, START_GAME_COMMAND))
        return this->onStartGameResponse(response);
    else if (!strcmp(response->header.command, INPUT_COMMAND))
        return this->onSendKeyResponse(response);
    else
        throw std::runtime_error("Invalid response command");

    this->startReceive();
}

void Client::Network::onServerMessage(Message* message)
{
    if (!strcmp(message->header.command, SERVER_COMMAND_CHECK_CONNECTION))
        return this->onCheckConnectionMessage(message);
    else
        throw std::runtime_error("Invalid message command");

    this->startReceive();
}



/* --------------------------------------------------- */
/* ---------------- Connect to server ---------------- */
/* --------------------------------------------------- */
void Client::Network::connectToServer()
{
    this->sendMessage(CONNECT_TO_SERVER_COMMAND, nullptr);
}

void Client::Network::onConnectToServerResponse(Response* response)
{
    this->clientId = response->header.clientId;

    std::cout << "Server response: " << response->header.statusMessage << std::endl;
    std::cout << "Connected to server: " << this->remoteEndpoint << std::endl;
    std::cout << "Client id: " << this->clientId << std::endl << std::endl;
}
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */



/* --------------------------------------------------- */
/* ------------------ Update  Name ------------------- */
/* --------------------------------------------------- */
void Client::Network::updateName(std::string name)
{
    if (name.length() > MAX_NAME_LENGTH)
        throw std::runtime_error("The name is too long");

    UpdateNameData data;
    strcpy(data.name, name.c_str());
    this->sendMessage(UPDATE_NAME_COMMAND, (char*)&data);
}

void Client::Network::onUpdateNameResponse(Response* response)
{
    UpdateNameData* data = (UpdateNameData*)response->data;
    this->name = data->name;

    std::cout << "Name successfully updated: " << this->name << std::endl;
}
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */



/* --------------------------------------------------- */
/* ------------------- Join  Room -------------------- */
/* --------------------------------------------------- */
void Client::Network::joinRoom(int roomId)
{
    JoinRoomData data;
    data.roomId = roomId;
    this->sendMessage(JOIN_ROOM_COMMAND, (char*)&data);
}

void Client::Network::onJoinRoomResponse(Response* response)
{
    JoinRoomData* data = (JoinRoomData*)response->data;
    this->roomId = data->roomId;

    std::cout << "Joined room: " << this->roomId << std::endl;
}
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */



/* --------------------------------------------------- */
/* -------------------- Send Key --------------------- */
/* --------------------------------------------------- */
void Client::Network::sendKey(std::string key)
{
    InputData data;
    strcpy(data.key, key.c_str());
    this->sendMessage(INPUT_COMMAND, (char*)&data);
}

void Client::Network::onSendKeyResponse(Response* response)
{
    InputData* data = (InputData*)response->data;

    std::cout << "Key successfully received: " << data->key << std::endl;
}
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */



/* --------------------------------------------------- */
/* ------------------ Check Connection --------------- */
/* --------------------------------------------------- */
void Client::Network::startGame(int roomId)
{
    StartGameData data;
    data.roomId = roomId;
    this->sendMessage(START_GAME_COMMAND, (char*)&data);
}

void Client::Network::onStartGameResponse(Response* response)
{
    StartGameData* data = (StartGameData*)response->data;

    std::cout << "Game started in room: " << data->roomId << std::endl << std::endl;
}
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */


void Client::Network::onCheckConnectionMessage(Message* message)
{
    (void)message;
    Response response = this->createResponse(
        SERVER_COMMAND_CHECK_CONNECTION,
        "OK"
    );

    return this->sendResponse(response);
}

void Client::Network::setClientId(int id)
{
    this->clientId = id;
}

int Client::Network::getClientId() const
{
    return this->clientId;
}

void Client::Network::setRoomId(int id)
{
    this->roomId = id;
}

int Client::Network::getRoomId() const
{
    return this->roomId;
}

void Client::Network::setName(std::string name)
{
    this->name = name;
}

std::string Client::Network::getName() const
{
    return this->name;
}

void Client::Network::setEndpoint(
    std::string &ip,
    std::string &port
)
{
    boost::asio::ip::udp::resolver resolver(io);
    this->remoteEndpoint = *resolver.resolve(
        boost::asio::ip::udp::v4(),
        ip,
        port
    ).begin();
    this->socket.open(boost::asio::ip::udp::v4());
    this->clientId = -1;
}
