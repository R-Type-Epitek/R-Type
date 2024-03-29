//
// Created by Xavier VINCENT on 13/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"
#include "game/Game.hpp"

namespace Network
{
  /**
     * @brief Represents the state of a room.
     *
     * This enum is used to represent the state of a room in a networked
     * environment. The states are WAITING, RUNNING, and FINISHED.
     */
  enum RoomState
  {
    WAITING,
    RUNNING,
    FINISHED
  };

  /**
     * @brief Represents a room in the network context.
     *
     * This class encapsulates the properties of a room in a networked
     * environment, including its ID, size, and the players within the room.
     */
  class Room {
   public:
    /**
         * @brief Constructor for Room.
         *
         * Initializes a Room with a given ID and size.
         *
         * @param id The unique identifier for the room.
         * @param size The size of the room, typically representing its
         * capacity.
         */
    Room(int id, int size);

    /**
      * @brief Copy constructor for Room.
      *
      * @param room The room to copy.
      */
    Room(const Room& room);

    /**
      * @brief Move constructor for Room.
      *
      * @param room The room to move.
      */
    Room(Room&& room);

    /**
     * @brief Copy assignment operator for Room.
     * 
     * @param room The room to copy.
     * @return Room& A reference to the copied room.
     */
    Room& operator=(const Room& room);

    /**
      * @brief Move assignment operator for Room.
      * 
      * @param room The room to move.
      * @return Room& A reference to the moved room.
      */
    Room& operator=(Room&& room);

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
         * @return std::vector<int> A vector containing the IDs of the players
         * in the room.
         */
    std::vector<int> getPlayers();

    /**
         * @brief Gets the state of the room.
         *
         * @return RoomState The state of the room.
         */
    RoomState getState() const;

    /**
         * @brief Sets the state of the room.
         *
         * @param state The new state of the room.
         */
    void setState(RoomState state);

    /**
         * @brief Checks if the room is full.
         *
         * @return true If the room is full.
         * @return false If the room is not full.
         */
    bool isFull() const;

    /**
     * @brief Gets the entities state buffer the room.
     *
     * @return Server::Game::Game The game hosted by the room.
     */
    std::vector<char> getEntitiesStateBuffer();

    /**
     * @brief Gets the game hosted by the room.
     *
     * @return Server::Game::Game The game hosted by the room.
     */
    Server::Game::Game& getHostedGame();

   protected:
   private:
    int size;                                         ///< The size of the room, typically its capacity.
    int id;                                           ///< The unique identifier of the room.
    std::vector<int> players;                         ///< A vector of player IDs currently in the room.
    RoomState state;                                  ///< The state of the room.
    std::unique_ptr<Server::Game::Game> m_hostedGame; ///< The game hosted by the room.
  };

} // namespace Network
