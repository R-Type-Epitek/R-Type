//
// Created by Xavier VINCENT on 13/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"

namespace Network
{
    /**
     * @brief Represents a room in the network context.
     *
     * This class encapsulates the properties of a room in a networked environment,
     * including its ID, size, and the players within the room.
     */
    class Room {
        public:
            /**
             * @brief Constructor for Room.
             * 
             * Initializes a Room with a given ID and size.
             *
             * @param id The unique identifier for the room.
             * @param size The size of the room, typically representing its capacity.
             */
            Room(int id, int size);

            /**
             * @brief Destructor for Room.
             */
            ~Room();

            /**
             * @brief Adds a player to the room.
             * 
             * @param id The ID of the player to be added.
             */
            void addPlayer(int id);

            /**
             * @brief Removes a player from the room.
             * 
             * @param id The ID of the player to be removed.
             */
            void removePlayer(int id);

            /**
             * @brief Gets the ID of the room.
             * 
             * @return int The ID of the room.
             */
            int getId() const;

            /**
             * @brief Sets the ID of the room.
             * 
             * @param id The new ID of the room.
             */
            void setId(int id);

            /**
             * @brief Gets the size of the room.
             * 
             * @return int The size of the room.
             */
            int getSize() const;

            /**
             * @brief Sets the size of the room.
             * 
             * @param size The new size of the room.
             */
            void setSize(int size);

            /**
             * @brief Gets the list of players in the room.
             * 
             * @return std::vector<int> A vector containing the IDs of the players in the room.
             */
            std::vector<int> getPlayers();

        protected:
        private:
            int size; ///< The size of the room, typically its capacity.
            int id; ///< The unique identifier of the room.
            std::vector<int> players; ///< A vector of player IDs currently in the room.
    };
}
