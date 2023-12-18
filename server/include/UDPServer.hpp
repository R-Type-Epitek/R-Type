//
// Created by Xavier VINCENT on 13/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"

namespace Network
{
    /**
     * @class UDPServer
     * @brief Manages a UDP server for handling network communication.
     * 
     * The UDPServer class provides functionalities to create and manage a server 
     * that communicates using the UDP protocol. It handles client connections, 
     * data transmission, and room management for network clients.
     */
    class UDPServer {
        public:
            /**
             * @brief Constructs a UDPServer with a specified I/O context.
             * 
             * Initializes a new UDPServer instance using the provided Boost ASIO I/O context. 
             * This constructor is typically used when the server's port is set separately.
             * 
             * @param io Reference to boost::asio::io_context for managing I/O operations.
             */
            UDPServer(boost::asio::io_context &io);

            /**
             * @brief Constructs a UDPServer with a specified I/O context and port.
             * 
             * Initializes a new UDPServer instance using the provided Boost ASIO I/O context and 
             * listens on the specified port. This constructor is convenient for initializing 
             * and starting the server in one step.
             * 
             * @param io Reference to boost::asio::io_context for managing I/O operations.
             * @param port Integer specifying the port number on which the server will listen.
             */
            UDPServer(boost::asio::io_context &io, int port);

            /**
             * @brief Destructor for UDPServer.
             * 
             * Cleans up resources used by the UDPServer instance. Ensures proper 
             * shutdown of the server and releases network resources.
             */
            ~UDPServer();

        protected:
        private:
            boost::asio::ip::udp::socket socket; ///< UDP socket for communication.
            std::vector<Network::Client> clients; ///< List of connected clients.
            boost::array<char, 1024> recvBuffer{}; ///< Buffer for receiving data.
            boost::asio::ip::udp::endpoint remoteEndpoint; ///< Endpoint for the remote connection.
            Network::ThreadSafeQueue<Message *> messageQueue; ///< Queue for thread-safe message handling.
            std::vector<std::thread> workers; ///< Worker threads for processing messages.
            std::vector<Network::Room> rooms; ///< Rooms available for client grouping.

            /**
             * @brief Initializes the server on a specified port.
             * 
             * Sets up the server to listen on the given port. This includes binding the socket 
             * and preparing it to receive incoming connections and data.
             * 
             * @param port Integer specifying the port number to listen on.
             */
            void initServer(int port);

            /**
             * @brief Initializes a specified number of rooms.
             * 
             * Creates and prepares a defined number of rooms for client interaction and game management.
             * 
             * @param count Integer specifying the number of rooms to initialize.
             */
            void initRooms(int count);

            /**
             * @brief Handles incoming data packets.
             * 
             * Processes received data from clients, handling any errors and managing the 
             * transfer of bytes. This function is called back by the Boost ASIO service.
             * 
             * @param error boost::system::error_code representing the error state.
             * @param bytesTransferred Size_t representing the number of bytes received.
             */
            void handleReceive(
                const boost::system::error_code &error,
                std::size_t bytesTransferred
            );

            /**
             * @brief Sends data to all connected clients.
             * 
             * Broadcasts a given data buffer to all clients currently connected to the server.
             * 
             * @param buffer const boost::asio::const_buffer& containing the data to send.
             */
            void sendToAll(const boost::asio::const_buffer &buffer);

            /**
             * @brief Sends data to a specific client.
             * 
             * Sends a data buffer to a client identified by its unique ID. This is used for targeted communication.
             * 
             * @param buffer const boost::asio::const_buffer& containing the data to send.
             * @param id Integer ID of the client to send data to.
             */
            void sendToClient(
                const boost::asio::const_buffer &buffer,
                int id
            );

            /**
             * @brief Starts the asynchronous receive operation.
             * 
             * Prepares the server to begin receiving data asynchronously. This sets up the 
             * socket to listen for incoming data and handle it appropriately.
             */
            void startReceive();

            /**
             * @brief Processes messages in the queue.
             * 
             * Takes messages from the queue and processes them accordingly. This function is 
             * typically run in a separate thread to handle client requests.
             * 
             * @param message Pointer to Message object to be processed.
             */
            void processMessage(Message *message);

            /**
             * @brief Function executed by worker threads.
             * 
             * Defines the tasks that worker threads will perform. This includes message processing 
             * and other server maintenance tasks.
             */
            void workerFunction();

            /**
             * @brief Creates a response message.
             * 
             * Constructs a response message to be sent to clients. This includes client ID, command details, 
             * status message, and status code.
             * 
             * @param clientId Integer ID of the client to receive the response.
             * @param command String representing the command to respond to.
             * @param statusMessage String containing a message describing the response status.
             * @param status Integer status code representing the outcome of the command.
             * @return Response object ready to be sent to the client.
             */
            Response createResponse(
                int clientId,
                const std::string& command,
                const std::string& statusMessage,
                int status
            );

            /**
             * @brief Sends a response to a client and logs it.
             * 
             * Sends a constructed Response object to the appropriate client and logs the action for server records.
             * 
             * @param response const Response& object containing the response data.
             */
            void sendResponseAndLog(const Response& response);

            // Command handling functions
            void helloCommand(Message *message); ///< Handles 'hello' command.
            void nameCommand(Message *message); ///< Handles 'name' command.
            void joinCommand(Message *message); ///< Handles 'join' command.
            void keyCommand(Message *message); ///< Handles 'key' command.
    };
}
