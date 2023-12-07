///*
//** EPITECH PROJECT, 2023
//** R-Type
//** File description:
//** Client
//*/

#include "network/UDPServer.hpp"

Network::UDPServer::UDPServer(boost::asio::io_context &io, int port) :
    socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    std::cout << "Server listening on port " << port << std::endl;
    this->start_receive();
}

Network::UDPServer::~UDPServer() {
    this->socket.close();
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
    if (error && error == boost::asio::error::message_size) {
        std::cout << "Error: " << error << std::endl;
        return;
    }
    this->process_message(
        std::string(this->recv_buffer.begin(), this->recv_buffer.begin() + bytes_transferred),
        bytes_transferred
    );
}

void Network::UDPServer::send_to_all(const std::string &message)
{
    for (auto &client : this->clients)
        this->socket.send_to(
            boost::asio::buffer(message),
            client.getEndpoint()
        );
}

void Network::UDPServer::send_to_client(const std::string &message, int id)
{
    this->socket.send_to(
        boost::asio::buffer(message),
        this->clients[id].getEndpoint()
    );
}

void Network::UDPServer::process_message(
    std::string message,
    std::size_t bytes_transferred
)
{
    if (message.substr(0, 4) == "id: ") {
        std::string new_message = message.substr(message.find("\n") + 1, message.size() - message.find("\n") - 1);
        int id = std::stoi(message.substr(4, message.find("\n") - 4));

        return this->handle_message_from_client(
            new_message,
            bytes_transferred,
            id
        );
    }
    return this->handle_message_from_guest(message, bytes_transferred);
}

void Network::UDPServer::handle_message_from_client(
    std::string message,
    std::size_t bytes_transferred,
    int id
)
{
    (void)bytes_transferred;
    Client client = this->clients[id];
    const boost::asio::ip::udp::endpoint &endpoint = client.getEndpoint();

    std::cout << "Client " << id << " (" << endpoint.address().to_string() << ":" << endpoint.port() << ")"  << " sent: " << message << std::endl;
    this->start_receive();
}

void Network::UDPServer::handle_message_from_guest(
    std::string message,
    std::size_t bytes_transferred
)
{
    (void)message;
    (void)bytes_transferred;
    int id = this->clients.size();
    Client client;

    client.setEndpoint(this->remote_endpoint);
    client.setId(id);
    this->clients.push_back(client);
    std::cout << "Client " << id << " connected (" << this->remote_endpoint.address().to_string() << ":" << this->remote_endpoint.port() << ")" << std::endl;
    this->send_to_client("WELCOME id: " + std::to_string(id) + "\n", id);
    this->start_receive();
}
