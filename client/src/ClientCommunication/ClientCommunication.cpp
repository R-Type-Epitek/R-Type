// File: client/src/Client/Client.cpp

#include "../../include/Client.hh"

client::ClientCommunication::ClientCommunication(std::size_t width, std::size_t height)
{
    sf::RenderWindow tmp(sf::RenderWindow(sf::VideoMode(width, height), "SFML Window"));
    this->window_ = tmp;
    this->socket_ = udp::socket(this->io_service_);
}

client::ClientCommunication::ClientCommunication(std::size_t width, std::size_t height, std::string address, unsigned short port)
{
    this->window_ = sf::RenderWindow(sf::VideoMode(width, height), "SFML Window");
    this->receiver_endpoint_ = udp::endpoint (boost::asio::ip::address::from_string(address), port);
    this->socket_ = udp::socket(this->io_service_);
    this->socket_.open(udp::v4());
}

void client::ClientCommunication::send_event(sf::Event event)
{
    //voir Xavier pour l'envoie en byte, provisoirement on envoie en string
    sf::Keyboard::Key send_buf = event.key.code;

    this->socket_.send_to(boost::asio::buffer(send_buf), this->receiver_endpoint_);
}