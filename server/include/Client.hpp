//
// Created by Xavier VINCENT on 13/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"

namespace Network
{
    /**
     * @brief Represents a network client.
     *
     * This class encapsulates the details of a network client, including its endpoint,
     * identifier, and name. It provides methods to get and set these properties.
     */
    class Client {
        public:
            /**
             * @brief Constructor for Client.
             *
             * Initializes a new Client instance with default values.
             */
            Client();

            /**
             * @brief Destructor for Client.
             */
            ~Client();

            /**
             * @brief Gets the network endpoint of the client.
             *
             * @return boost::asio::ip::udp::endpoint The endpoint of the client.
             */
            boost::asio::ip::udp::endpoint getEndpoint() const;

            /**
             * @brief Sets the network endpoint of the client.
             *
             * @param endpoint The new endpoint to be set for the client.
             */
            void setEndpoint(boost::asio::ip::udp::endpoint endpoint);

            /**
             * @brief Gets the identifier of the client.
             *
             * @return int The identifier of the client.
             */
            int getId() const;

            /**
             * @brief Sets the identifier of the client.
             *
             * @param id The new identifier to be set for the client.
             */
            void setId(int id);

            /**
             * @brief Gets the name of the client.
             *
             * @return std::string The name of the client.
             */
            std::string getName() const;

            /**
             * @brief Sets the name of the client.
             *
             * @param name The new name to be set for the client.
             */
            void setName(std::string name);

            /**
             * @brief Sets the identifier of the room.
             * 
             * @param roomId The new identifier to be set for the room.
             */
            void setRoomId(int roomId);

            /**
             * @brief Gets the identifier of the room.
             * 
             * @return int The identifier of the room.
             */
            int getRoomId() const;

        protected:
        private:
            boost::asio::ip::udp::endpoint endpoint; ///< The network endpoint of the client.
            int id; ///< The identifier of the client.
            std::string name; ///< The name of the client.
            int roomId; ///< The identifier of the room.
    };
}
