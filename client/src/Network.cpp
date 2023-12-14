//
// Created by Xavier VINCENT on 14/12/2023.
//

#include "Network.hpp"

Client::Network::Network(
    boost::asio::io_context &io,
    std::string ip,
    std::string port
): socket(io)
{
    boost::asio::ip::udp::resolver resolver(io);
    this->receiver_endpoint = *resolver.resolve(
        boost::asio::ip::udp::v4(),
        ip,
        port
    ).begin();
    this->socket.open(boost::asio::ip::udp::v4());
    this->client_id = -1;
}

Client::Network::~Network()
{
}

void Client::Network::send(
  const boost::asio::const_buffer &buffer
)
{
    this->socket.send_to(
        buffer,
        this->receiver_endpoint
    );
}

void Client::Network::connect_to_server()
{
    Message message;
    message.header.client_id = -1;
    strcpy(message.header.command, HELLO_COMMAND);
    message.header.dataLength = 0;

    boost::array<char, 1024> recv_buffer{};
    this->send(boost::asio::buffer(&message, sizeof(message)));
    this->socket.receive_from(
        boost::asio::buffer(recv_buffer),
        this->receiver_endpoint
    );
    Response *response = (Response *)recv_buffer.data();

    if (strcmp(response->header.command, HELLO_COMMAND) != 0)
        throw std::runtime_error("Invalid response command");

    this->client_id = response->header.client_id;

    std::cout << "Server response: " << response->header.status_message << std::endl;
    std::cout << "Connected to server: " << this->receiver_endpoint << std::endl;
    std::cout << "Client id: " << this->client_id << std::endl << std::endl;
}

void Client::Network::send_name(std::string name)
{
    if (this->client_id == -1)
        throw std::runtime_error("Not connected to server");

    if (name.length() > 32)
        throw std::runtime_error("Name too long");

    size_t totalSize = sizeof(MessageHeader) + sizeof(SendNameData);
    std::vector<char> messageBuffer(totalSize);

    MessageHeader header;
    header.client_id = this->client_id;
    strcpy(header.command, NAME_COMMAND);
    header.dataLength = sizeof(SendNameData);

    memcpy(messageBuffer.data(), &header, sizeof(header));

    SendNameData data;
    strcpy(data.name, name.c_str());
    memcpy(messageBuffer.data() + sizeof(header), &data, sizeof(data));
    this->send(boost::asio::buffer(messageBuffer.data(), messageBuffer.size()));

    boost::array<char, 1024> recv_buffer{};
    this->socket.receive_from(
        boost::asio::buffer(recv_buffer),
        this->receiver_endpoint
    );
    Response *response = (Response *)recv_buffer.data();

    if (strcmp(response->header.command, NAME_COMMAND) != 0)
        throw std::runtime_error("Invalid response command");

    if (response->header.status != 200)
        throw std::runtime_error(response->header.status_message);

    std::cout << "Server response: " << response->header.status_message << std::endl << std::endl;
}

void Client::Network::join_room(int room_id)
{
    if (this->client_id == -1)
        throw std::runtime_error("Not connected to server");

    size_t totalSize = sizeof(MessageHeader) + sizeof(JoinRoomData);
    std::vector<char> messageBuffer(totalSize);

    MessageHeader header;
    header.client_id = this->client_id;
    strcpy(header.command, JOIN_COMMAND);
    header.dataLength = sizeof(JoinRoomData);

    memcpy(messageBuffer.data(), &header, sizeof(header));

    JoinRoomData data;
    data.room_id = room_id;
    memcpy(messageBuffer.data() + sizeof(header), &data, sizeof(data));
    this->send(boost::asio::buffer(messageBuffer.data(), messageBuffer.size()));

    boost::array<char, 1024> recv_buffer{};
    this->socket.receive_from(
        boost::asio::buffer(recv_buffer),
        this->receiver_endpoint
    );
    Response *response = (Response *)recv_buffer.data();

    if (strcmp(response->header.command, JOIN_COMMAND) != 0)
        throw std::runtime_error("Invalid response command");

    if (response->header.status != 200)
        throw std::runtime_error(response->header.status_message);

    this->room_id = room_id;

    std::cout << "Server response: " << response->header.status_message << std::endl << std::endl;
}

void Client::Network::setClientId(int id)
{
    this->client_id = id;
}

int Client::Network::getClientId() const
{
    return this->client_id;
}

void Client::Network::setRoomId(int id)
{
    this->room_id = id;
}

int Client::Network::getRoomId() const
{
    return this->room_id;
}

void Client::Network::setName(std::string name)
{
    this->name = name;
}

std::string Client::Network::getName() const
{
    return this->name;
}
