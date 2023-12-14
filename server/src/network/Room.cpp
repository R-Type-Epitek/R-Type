//
// Created by Xavier VINCENT on 13/12/2023.
//

#include "network/Room.hpp"

Network::Room::Room(int id, int size): size(size), id(id)
{
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
