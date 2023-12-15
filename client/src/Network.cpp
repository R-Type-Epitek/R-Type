//
// Created by Xavier VINCENT on 14/12/2023.
//

#include "../include/Network.hpp"

client::Network::Network(
    std::string ip,
    std::string port
): socket(io)
{
    boost::asio::ip::udp::resolver resolver(this->io);
    this->receiver_endpoint = *resolver.resolve(
        boost::asio::ip::udp::v4(),
        ip,
        port
    ).begin();
    this->socket.open(boost::asio::ip::udp::v4());
    this->client_id = -1;
    this->io.run();
}

void client::Network::send(
  const boost::asio::const_buffer &buffer
)
{
    this->socket.send_to(
        buffer,
        this->receiver_endpoint
    );
}

void client::Network::send_message(
    const std::string& command,
    const char* data,
    size_t dataSize
)
{
    size_t totalSize = sizeof(MessageHeader) + dataSize;
    std::vector<char> messageBuffer(totalSize);

    MessageHeader header;
    header.client_id = this->client_id;
    strcpy(header.command, command.c_str());
    header.dataLength = dataSize;

    memcpy(messageBuffer.data(), &header, sizeof(header));
    if (dataSize > 0)
        memcpy(messageBuffer.data() + sizeof(header), data, dataSize);

    this->send(boost::asio::buffer(messageBuffer.data(), messageBuffer.size()));
}

Response* client::Network::receive_and_validate_response(
    const std::string& expectedCommand
)
{
    boost::array<char, 1024> recv_buffer{};
    this->socket.receive_from(boost::asio::buffer(recv_buffer), this->receiver_endpoint);
    Response* response = (Response*)recv_buffer.data();

    if (strcmp(response->header.command, expectedCommand.c_str()) != 0)
        throw std::runtime_error("Invalid response command");

    if (response->header.status != 200)
        throw std::runtime_error(response->header.status_message);

    return response;
}

void client::Network::connect_to_server()
{
    this->send_message(HELLO_COMMAND, nullptr, 0);
    Response* response = receive_and_validate_response(HELLO_COMMAND);

    this->client_id = response->header.client_id;

    std::cout << "Server response: " << response->header.status_message << std::endl;
    std::cout << "Connected to server: " << this->receiver_endpoint << std::endl;
    std::cout << "Client id: " << this->client_id << std::endl << std::endl;
}

void client::Network::send_name(std::string name)
{
    if (name.length() > MAX_NAME_LENGTH)
        throw std::runtime_error(NAME_TOO_LONG);

    SendNameData data;
    strcpy(data.name, name.c_str());
    this->send_message(NAME_COMMAND, (char*)&data, sizeof(data));
    
    Response* response = receive_and_validate_response(NAME_COMMAND);
    this->name = name;

    std::cout << "Server response: " << response->header.status_message << std::endl << std::endl;
}

void client::Network::join_room(int room_id)
{
    JoinRoomData data;
    data.room_id = room_id;
    this->send_message(JOIN_COMMAND, (char*)&data, sizeof(data));

    Response* response = receive_and_validate_response(JOIN_COMMAND);
    this->room_id = room_id;

    std::cout << "Server response: " << response->header.status_message << std::endl << std::endl;
}

void client::Network::setClientId(int id)
{
    this->client_id = id;
}

int client::Network::getClientId() const
{
    return this->client_id;
}

void client::Network::setRoomId(int id)
{
    this->room_id = id;
}

int client::Network::getRoomId() const
{
    return this->room_id;
}

void client::Network::setName(std::string name)
{
    this->name = name;
}

std::string client::Network::getName() const
{
    return this->name;
}

void client::Network::set_endpoint(
    std::string &ip,
    std::string &port
)
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
