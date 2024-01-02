//
// Created by Xavier VINCENT on 13/12/2023.
//

#include "RTypeNetwork.hpp"

Network::Client::Client()
  : id(-1)
  , name("")
  , roomId(-1)
  , lastMessageTime(std::chrono::steady_clock::now())
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

void Network::Client::setRoomId(int roomId)
{
  this->roomId = roomId;
}

int Network::Client::getRoomId() const
{
  return this->roomId;
}

void Network::Client::updateLastMessageTime()
{
  this->lastMessageTime = std::chrono::steady_clock::now();
}

bool Network::Client::isInactiveFor(long milliseconds)
{
  auto now = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(now - this->lastMessageTime).count() >
    milliseconds;
}
