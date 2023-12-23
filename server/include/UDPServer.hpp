//
// Created by Xavier VINCENT on 13/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"

/**
 * @brief Used to represent a message with a timestamp.
 * 
 * This struct is used to represent a message with a timestamp. It is used to
 * track the time at which a message was received.
 * 
 * @see Message
*/
struct TimedMessage {
    Message *message; ///< Pointer to the message.
    std::chrono::high_resolution_clock::time_point timestamp; ///< Timestamp of the message.
};

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

            /**
             * @brief Gets the UDP socket used by the server.
             * 
             * Returns a reference to the UDP socket used by the server for communication.
             * 
             * @return Reference to the UDP socket.
             */
            boost::asio::ip::udp::socket& getSocket();

            /**
             * @brief Gets the list of connected clients.
             * 
             * Returns a vector containing the list of clients currently connected to the server.
             * 
             * @return Vector containing the list of connected clients.
             */
            std::vector<Network::Client>& getClients();

            /**
             * @brief Gets the receive buffer.
             * 
             * Returns a boost::array containing the receive buffer used by the server.
             * 
             * @return boost::array containing the receive buffer.
             */
            boost::array<char, 1024> getRecvBuffer() const;

            /**
             * @brief Gets the remote endpoint.
             * 
             * Returns a boost::asio::ip::udp::endpoint containing the remote endpoint.
             * 
             * @return boost::asio::ip::udp::endpoint containing the remote endpoint.
             */
            boost::asio::ip::udp::endpoint getRemoteEndpoint() const;

            /**
             * @brief Gets the list of rooms.
             * 
             * Returns a vector containing the list of rooms currently available on the server.
             * 
             * @return Vector containing the list of rooms.
             */
            std::vector<Network::Room>& getRooms();

            /**
             * @brief Adds a client.
             * 
             * Adds the specified client to the list of connected clients.
             * 
             * @param client Network::Client to add.
            */
            void addClient(Network::Client client);

            /**
             * @brief Initializes the server.
             * 
             * Initializes the server by binding the socket to the specified port and
             * starting the worker threads.
             * 
             * @param port Integer specifying the port number on which the server will listen.
            */
            void initServer(int port);

            /**
             * @brief Init the rooms.
             * 
             * Initializes the rooms by creating the specified number of rooms.
             * 
             * @param count Integer specifying the number of rooms to create.
             */
            void initRooms(int count);

            /**
             * @brief Start to receive data.
             * 
             * Start to listen for incoming data on the socket.
            */
            void startReceive();

            /**
             * @brief Handle receive data.
             * 
             * Handle the received data by creating a new TimedMessage and pushing it into the message queue.
            */
            void handleReceive(
                const boost::system::error_code &error,
                std::size_t bytes_transferred
            );

            /**
             * @brief Send data to all clients.
             * 
             * Send the specified data to all clients connected to the server.
             * 
             * @param buffer boost::asio::const_buffer containing the data to send.
            */
            void sendToAll(
                const boost::asio::const_buffer &buffer
            );

            /**
             * @brief Send data to all clients in a room.
             * 
             * Send the specified data to all clients in the room with the specified ID.
             * 
             * @param buffer boost::asio::const_buffer containing the data to send.
             * @param roomId Integer specifying the ID of the room to send the data to.
            */
            void sendToAllClientsInRoom(
                const boost::asio::const_buffer &buffer,
                int roomId
            );

            /**
             * @brief Send data to a specific client.
             * 
             * Send the specified data to the client with the specified ID.
             * 
             * @param buffer boost::asio::const_buffer containing the data to send.
             * @param id Integer specifying the ID of the client to send the data to.
            */
            void sendToClient(
                const boost::asio::const_buffer &buffer,
                int id
            );

            /**
             * @brief Process a TimedMessage.
             * 
             * Process the specified TimedMessage by calling the appropriate command handler.
            */
            void processMessage(TimedMessage message);

            /**
             * @brief Process a Response.
             * 
             * Process the specified Response by sending it to the client and logging it.
             * 
             * @param response Response to process.
            */
            void processResponse(Response *response);

            /**
             * @brief Function executed by worker threads.
             * 
             * Function executed by worker threads. It pops a TimedMessage from the message queue,
             * logged the message header and calls the processMessage function.
            */
            void workerFunction();

            /**
             * @brief Create a response.
             * 
             * Create a response to a client command.
             * 
             * @param clientId Integer specifying the ID of the client to send the response to.
             * @param command String containing the command to which the response is sent.
             * @param statusMessage String containing the status message to send.
             * @param data Pointer to the data to send.
             * @param status Integer specifying the status code to send.
             * 
             * @return Response containing the response to send.
            */
            Response createResponse(
                int clientId,
                const std::string& command,
                const std::string& statusMessage,
                const char data[] = nullptr,
                int dataSize = 0,
                int status = RES_SUCCESS
            );

            /**
             * @brief Send a response and log it.
             * 
             * Send the specified response to the client with the specified ID and log it.
             * 
             * @param timedMessage TimedMessage containing the message to which the response is sent.
             * @param response Response containing the response to send.
            */
            void sendResponseAndLog(
                TimedMessage timedMessage,
                const Response& response
            );

            /**
             * @brief Check if a client is registered.
             * 
             * Check if the client with the specified ID is registered to the server.
             * 
             * @param clientId Integer specifying the ID of the client to check.
             * 
             * @return Boolean indicating whether the client is registered.
            */
            bool isClientRegistered(int clientId);

            /**
             * @brief Check if a client is connected.
             * 
             * Check if the specified client is connected to the server.
             * 
             * @param clientId Integer specifying the ID of the client to check.
             * 
             * @return Boolean indicating whether the client is connected.
             */
            bool isClientConnected(int clientId);

            /**
             * @brief Start clientsConnectionTimer.
             * 
             * Start the timer for checking client connections.
             */
            void startCheckClientsConnectionTimer();

            /**
             * @brief Check clients.
             * 
             * Check the list of clients and remove disconnected clients.
             */
            void checkClients();

            /**
             * @brief Register command handlers.
             * 
             * Register all command handlers for the server.
             * 
             * @see ICommandHandler
            */
            void registerCommandHandlers();

        protected:
        private:
            boost::asio::ip::udp::socket socket; ///< UDP socket for communication.
            std::vector<Network::Client> clients; ///< List of connected clients.
            boost::array<char, 1024> recvBuffer{}; ///< Buffer for receiving data.
            boost::asio::ip::udp::endpoint remoteEndpoint; ///< Endpoint for the remote connection.
            Network::ThreadSafeQueue<TimedMessage> messageQueue; ///< Queue for thread-safe message handling.
            std::vector<std::thread> workers; ///< Worker threads for processing messages.
            std::vector<Network::Room> rooms; ///< Rooms available for client grouping.
            std::unordered_map<std::string, std::unique_ptr<ICommandHandler>> commandHandlers; ///< Command handlers for the server.
            boost::asio::steady_timer clientsConnectionTimer; ///< Timer for checking client connections.

            void handleInvalidClient(TimedMessage timedMessage); ///< Handles invalid client.
            void handleInvalidCommand(TimedMessage timedMessage); ///< Handles invalid command.
    };
}
