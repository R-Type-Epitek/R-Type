///*
//** EPITECH PROJECT, 2023
//** R-Type
//** File description:
//** Client
//*/

#include "network/Client.hpp"

Network::Client::Client()
{
}

Network::Client::~Client()
{
}

boost::asio::ip::udp::endpoint Network::Client::getEndpoint() const
{
    return this->endpoint;
}

void Network::Client::setEndpoint(boost::asio::ip::udp::endpoint endpoint)
{
    this->endpoint = endpoint;
}

int Network::Client::getId() const
{
    return this->id;
}

void Network::Client::setId(int id)
{
    this->id = id;
}

std::string Network::Client::getName() const
{
    return this->name;
}

void Network::Client::setName(std::string name)
{
    this->name = name;
}