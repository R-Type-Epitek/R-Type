//
// Created by Xavier VINCENT on 13/12/2023.
//

#pragma once
#include <vector>

namespace Network
{
    class Room {
        public:
            Room(int id, int size);
            ~Room();
            void addPlayer(int id);
            void removePlayer(int id);
            int getId() const;
            void setId(int id);
            int getSize() const;
            void setSize(int size);
            std::vector<int> getPlayers();

        protected:
        private:
            int size;
            int id;
            std::vector<int> players;
    };
}
