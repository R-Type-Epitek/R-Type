//
// Created by Xavier VINCENT on 14/12/2023.
//

#include "../include/Network.hpp"

Client::Network::Network(
    std::string ip,
    std::string port
): socket(io)
{
    boost::asio::ip::udp::resolver resolver(this->io);
    this->receiverEndpoint = *resolver.resolve(
        boost::asio::ip::udp::v4(),
        ip,
        port
    ).begin();
    this->socket.open(boost::asio::ip::udp::v4());
    this->clientId = -1;
    this->io.run();
}

void Client::Network::send(
  const boost::asio::const_buffer &buffer
)
{
    this->socket.send_to(
        buffer,
        this->receiverEndpoint
    );
}

void Client::Network::sendMessage(
    const std::string& command,
    const char* data,
    size_t dataSize
)
{
    size_t totalSize = sizeof(MessageHeader) + dataSize;
    std::vector<char> messageBuffer(totalSize);

    MessageHeader header;
    header.clientId = this->clientId;
    strcpy(header.command, command.c_str());
    header.dataLength = dataSize;

    memcpy(messageBuffer.data(), &header, sizeof(header));
    if (dataSize > 0)
        memcpy(messageBuffer.data() + sizeof(header), data, dataSize);

    this->send(boost::asio::buffer(messageBuffer.data(), messageBuffer.size()));
}

Response* Client::Network::receiveAndValidateResponse(
    const std::string& expectedCommand
)
{
    boost::array<char, 1024> recv_buffer{};
    this->socket.receive_from(boost::asio::buffer(recv_buffer), this->receiverEndpoint);
    Response* response = (Response*)recv_buffer.data();

    if (strcmp(response->header.command, expectedCommand.c_str()) != 0)
        throw std::runtime_error("Invalid response command");

    if (response->header.status != 200)
        throw std::runtime_error(response->header.status_message);

    return response;
}

void Client::Network::connectToServer()
{
    this->sendMessage(HELLO_COMMAND, nullptr, 0);
    Response* response = receiveAndValidateResponse(HELLO_COMMAND);

    this->clientId = response->header.clientId;

    std::cout << "Server response: " << response->header.status_message << std::endl;
    std::cout << "Connected to server: " << this->receiverEndpoint << std::endl;
    std::cout << "Client id: " << this->clientId << std::endl << std::endl;
}

void Client::Network::sendName(std::string name)
{
    if (name.length() > MAX_NAME_LENGTH)
        throw std::runtime_error(NAME_TOO_LONG);

    SendNameData data;
    strcpy(data.name, name.c_str());
    this->sendMessage(NAME_COMMAND, (char*)&data, sizeof(data));
    
    Response* response = receiveAndValidateResponse(NAME_COMMAND);
    this->name = name;

    std::cout << "Server response: " << response->header.status_message << std::endl << std::endl;
}

void Client::Network::joinRoom(int roomId)
{
    JoinRoomData data;
    data.roomId = roomId;
    this->sendMessage(JOIN_COMMAND, (char*)&data, sizeof(data));

    Response* response = receiveAndValidateResponse(JOIN_COMMAND);
    this->roomId = roomId;

    std::cout << "Server response: " << response->header.status_message << std::endl << std::endl;
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
    this->receiverEndpoint = *resolver.resolve(
        boost::asio::ip::udp::v4(),
        ip,
        port
    ).begin();
    this->socket.open(boost::asio::ip::udp::v4());
    this->clientId = -1;
}
