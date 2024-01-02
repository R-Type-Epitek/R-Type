//
// Created by Xavier VINCENT on 13/12/2023.
//

#include "RTypeNetwork.hpp"

Network::Room::Room(int id, int size)
  : size(size)
  , id(id)
  , state(WAITING)
{
  this->m_hostedGame.load();
}

Network::Room::Room(const Room& room)
  : size(room.size)
  , id(room.id)
  , players(room.players)
  , state(room.state)
{
}

Network::Room::Room(Room&& room)
  : size(room.size)
  , id(room.id)
  , players(std::move(room.players))
  , state(room.state)
{
}

Network::Room& Network::Room::operator=(const Room& room)
{
  this->size = room.size;
  this->id = room.id;
  this->state = room.state;
  this->players = room.players;
  return *this;
}

Network::Room& Network::Room::operator=(Room&& room)
{
  this->size = room.size;
  this->id = room.id;
  this->state = room.state;
  this->players = std::move(room.players);
  return *this;
}

Network::Room::~Room()
{
}

void Network::Room::addPlayer(int id)
{
  this->players.push_back(id);
}

void Network::Room::removePlayer(int id)
{
  for (size_t i = 0; i < this->players.size(); i++) {
    if (this->players[i] == id) {
      this->players.erase(this->players.begin() + i);
      return;
    }
  }
}

int Network::Room::getId() const
{
  return this->id;
}

void Network::Room::setId(int id)
{
  this->id = id;
}

int Network::Room::getSize() const
{
  return this->size;
}

void Network::Room::setSize(int size)
{
  this->size = size;
}

std::vector<int> Network::Room::getPlayers()
{
  return this->players;
}

Network::RoomState Network::Room::getState() const
{
  return this->state;
}

void Network::Room::setState(RoomState state)
{
  this->state = state;
}

bool Network::Room::isFull() const
{
  return (int)this->players.size() == this->size;
}

Server::Game::RtypeGame& Network::Room::getHostedGame()
{
  return this->m_hostedGame;
}
