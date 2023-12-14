/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** UDPServer
*/

#include "network/UDPServer.hpp"

Network::UDPServer::UDPServer(boost::asio::io_context &io):
    socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), std::stoi(DEFAULT_PORT)))
{
    this->init_server(std::stoi(DEFAULT_PORT));
}

Network::UDPServer::UDPServer(boost::asio::io_context &io, int port):
    socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    this->init_server(port);
}

Network::UDPServer::~UDPServer() {
    this->socket.close();
}

void Network::UDPServer::init_server(int port)
{
    std::cout << "Server listening on port " << port << std::endl;
    this->init_rooms(NUMBER_OF_ROOMS);
    this->start_receive();
}

void Network::UDPServer::init_rooms(int count)
{
    for (int i = 0; i < count; i++) {
        Network::Room room(i, DEFAULT_ROOM_SIZE);

        this->rooms.push_back(room);
    }
    std::cout << "Rooms initialized" << "(" << count << ")" << std::endl;
}

void Network::UDPServer::start_receive()
{
    this->socket.async_receive_from(
        boost::asio::buffer(this->recv_buffer),
        this->remote_endpoint,
        boost::bind(
            &Network::UDPServer::handle_receive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Network::UDPServer::handle_receive(
    const boost::system::error_code &error,
    std::size_t bytes_transferred
)
{
    (void)bytes_transferred;
    if (error && error == boost::asio::error::message_size) {
        std::cout << "Error: " << error << std::endl;
        return;
    }
    this->process_message(boost::asio::buffer(this->recv_buffer));
}

void Network::UDPServer::send_to_all(
    const boost::asio::const_buffer &buffer
)
{
    for (auto &client : this->clients)
        this->socket.send_to(
            buffer,
            client.getEndpoint()
        );
}

void Network::UDPServer::send_to_client(
    const boost::asio::const_buffer &buffer,
    int id
)
{
    this->socket.send_to(
        buffer,
        this->clients[id].getEndpoint()
    );
}

void Network::UDPServer::process_message(
    const boost::asio::const_buffer &buffer
)
{
    Message *message = (Message *)buffer.data();

    if (!strcmp(message->header.command, HELLO_COMMAND))
        return this->hello_command(message);
    if (!strcmp(message->header.command, NAME_COMMAND))
        return this->name_command(message);
    if (!strcmp(message->header.command, JOIN_COMMAND))
        return this->join_command(message);

    throw std::runtime_error("Invalid command");
}

Response Network::UDPServer::create_response(
    int client_id,
    const std::string& command,
    const std::string& status_message,
    int status = RES_SUCCESS
)
{
    Response response;

    response.header.client_id = client_id;
    strcpy(response.header.command, command.c_str());
    response.header.dataLength = 0;
    response.header.status = status;
    strcpy(response.header.status_message, status_message.c_str());
    return response;
}

void Network::UDPServer::send_response_and_log(const Response& response)
{
    this->send_to_client(
        boost::asio::buffer(&response, sizeof(response)),
        response.header.client_id
    );
    std::cout << "Client " << response.header.client_id << ": " << response.header.status_message << std::endl;
    this->start_receive();
}

void Network::UDPServer::hello_command(Message *message)
{
    (void)message;

    int client_id = this->clients.size();
    std::string status_message = "User correctly connected to server";
    Response response = create_response(client_id, HELLO_COMMAND, status_message);

    Network::Client client;
    client.setEndpoint(this->remote_endpoint);
    client.setId(client_id);
    this->clients.push_back(client);

    send_response_and_log(response);
}

void Network::UDPServer::name_command(Message *message)
{
    SendNameData *data = (SendNameData *)message->data;
    std::string status_message = "Name correctly set: " + std::string(data->name);
    Response response = create_response(message->header.client_id, NAME_COMMAND, status_message);

    this->clients[message->header.client_id].setName(data->name);

    send_response_and_log(response);
}

void Network::UDPServer::join_command(Message *message)
{
    JoinRoomData *data = (JoinRoomData *)message->data;
    std::string status_message = "Joined room: " + std::to_string(data->room_id);
    Response response = create_response(message->header.client_id, JOIN_COMMAND, status_message);

    this->rooms[data->room_id].addPlayer(message->header.client_id);

    send_response_and_log(response);
}
