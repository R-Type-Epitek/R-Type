//
// Created by Xavier VINCENT on 14/12/2023.
//

#pragma once
#include "Constants.hpp"
#include "gameEngine/constants/Keybinds.hpp"
#include "gameEngine/network/Commands.hpp"
#include "gameEngine/network/Messages.hpp"
#include "gameEngine/network/Responses.hpp"
#include "gameEngine/network/Statuses.hpp"
#include "network/commands/IHandler.hpp"
#include "network/commands/Tracker.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>

namespace Client
{
  /**
   * @brief Class responsible for network operations in a client.
   *
   * The Network class handles all network communications for a client, including
   * sending and receiving messages and responses, managing command handlers, and
   * keeping track of client and room states.
   */
  class Network {
   public:
    /**
     * @brief Construct a new Network object.
     *
     * @param ip The IP address of the server to connect to.
     * @param port The port number for the network connection.
     */
    Network(std::string ip, std::string port);

    /**
     * @brief Default destructor for Network.
     */
    ~Network();

    /**
     * @brief Register command handlers for different types of network commands.
     *
     * This function initializes and sets up command handlers that will be used
     * to process various commands received over the network.
     */
    void registerCommandHandlers();

    /**
     * @brief Get the command handler for a specific command.
     *
     * @param name The name of the command for which the handler is required.
     * @return std::shared_ptr<ICommandHandler> Shared pointer to the requested command handler.
     */
    std::shared_ptr<ICommandHandler> getCommandHandler(std::string const &name);

    /**
     * @brief Send raw data over the network.
     *
     * @param buffer The constant buffer containing data to be sent.
     */
    void send(boost::asio::const_buffer const &buffer);

    /**
     * @brief Callback function for handling data sent over the network.
     *
     * @param error Boost ASIO error code indicating the status of the send operation.
     * @param bytesTransferred The number of bytes sent over the network.
     */
    void handleSend(boost::system::error_code const &error, std::size_t bytesTransferred);

    /**
     * @brief Send a command message over the network.
     *
     * @param command The command to be sent.
     * @param data Optional data to be sent with the command.
     * @param dataSize The size of the data being sent.
     */
    void sendMessage(std::string const &command, char const data[] = nullptr, int dataSize = 0);

    /**
     * @brief Send a response message over the network.
     *
     * @param command The command associated with the response.
     * @param statusMessage The status message to be sent.
     * @param data Optional data to be included in the response.
     * @param dataSize The size of the data being sent.
     * @param status The status code of the response (default is RES_SUCCESS).
     */
    void sendResponse(
      std::string const &command,
      std::string const &statusMessage,
      char const data[] = nullptr,
      int dataSize = 0,
      int status = RES_SUCCESS);

    /**
     * @brief Start the process of receiving data from the network.
     *
     * This function sets up the network to begin receiving data, setting up
     * the necessary callbacks and buffers for handling incoming data.
     */
    void startReceive();

    /**
     * @brief Callback function for handling data received from the network.
     *
     * @param error Boost ASIO error code indicating the status of the receive operation.
     * @param bytesTransferred The number of bytes received from the network.
     */
    void onReceive(boost::system::error_code const &error, std::size_t bytesTransferred);

    /**
     * @brief Handle a server response.
     *
     * This function processes a response received from the server.
     *
     * @param response Pointer to the Response object received from the server.
     */
    void onServerResponse(Response *response);

    /**
     * @brief Handle a server message.
     *
     * This function processes a message received from the server.
     *
     * @param message Pointer to the Message object received from the server.
     */
    void onServerMessage(Message *message);

    /**
     * @brief Handle a check connection message from the server.
     *
     * This function processes a message specifically intended to check the
     * connection status between the client and the server.
     *
     * @param message Pointer to the Message object received from the server.
     */
    void onCheckConnectionMessage(Message *message);

    /**
     * @brief Handle an update game message from the server.
     *
     * This function processes a message received from the server that contains
     * updates related to the game state.
     *
     * @param message Pointer to the Message object received from the server.
     */
    void onUpdateGameMessage(Message *message);

    /**
     * @brief Set the client's ID.
     *
     * @param id The new ID to be set for the client.
     */
    void setClientId(int id);

    /**
     * @brief Get the client's ID.
     *
     * @return int The current ID of the client.
     */
    int getClientId() const;

    /**
     * @brief Set the ID of the room the client is connected to.
     *
     * @param id The ID of the room to be set.
     */
    void setRoomId(int id);

    /**
     * @brief Get the ID of the room the client is connected to.
     *
     * @return int The current room ID.
     */
    int getRoomId() const;

    /**
     * @brief Set the name of the client.
     *
     * @param name The new name to be set for the client.
     */
    void setName(std::string name);

    /**
     * @brief Get the name of the client.
     *
     * @return std::string The current name of the client.
     */
    std::string getName() const;

    /**
     * @brief Set the remote endpoint for the network connection.
     *
     * @param ip The IP address of the remote endpoint.
     * @param port The port number of the remote endpoint.
     */
    void setRemoteEndpoint(std::string &ip, std::string &port);

    /**
     * @brief Get the remote endpoint of the network connection.
     *
     * @return boost::asio::ip::udp::endpoint The current remote endpoint.
     */
    boost::asio::ip::udp::endpoint getRemoteEndpoint() const;

    /**
     * @brief Get the queue of serialized ECS data.
     *
     * This function returns a reference to the queue holding serialized data
     * from the Entity Component System (ECS), ready for network transmission.
     *
     * @return QueueEcsSerialized& Reference to the queue of serialized ECS data.
     */
    using QueueEcsSerialized = std::vector<std::vector<char>>;
    QueueEcsSerialized &getSerializedEcsQueue();

    // Commands
    /**
     * @brief Execute a command with a specified action.
     *
     * This template function allows for the execution of a command along with a
     * specified action. It can be used to handle various command types dynamically.
     *
     * @tparam T The type of the command.
     * @tparam Func The function type for the action to be executed.
     * @param commandName The name of the command to execute.
     * @param action The action to be performed in association with the command.
     */
    template<typename T, typename Func>
    void executeCommand(const std::string &commandName, Func action);

    /**
     * @brief Connect to a server.
     *
     * This function initiates a connection to the server using the network parameters.
     */
    void connectToServer();

    /**
     * @brief Update the client's name.
     *
     * @param name The new name to be set for the client.
     */
    void updateName(std::string name);

    /**
     * @brief Join a room with a specified room ID.
     *
     * @param roomId The ID of the room to join.
     */
    void joinRoom(int roomId);

    /**
     * @brief Join a room automatically.
     *
     * This function sends a request to the server to join a room automatically.
     */
    void joinRoomAuto();

    /**
     * @brief Kick a player.
     *
     * This function sends a request to the server to kick a player.
     */
    void kickPlayer(int clientId);

    /**
     * @brief Send a key command to the server.
     *
     * @param key The key command to be sent.
     */
    void sendKey(GameEngine::Keybinds key);

    /**
     * @brief Join a game with a specified room ID.
     *
     * @param roomId The ID of the game room to join.
     */
    void joinGame(int roomId);

   protected:
   private:
    boost::asio::io_context io;
    boost::array<char, 65536> recvBuffer {};
    boost::asio::ip::udp::endpoint remoteEndpoint;
    boost::asio::ip::udp::socket socket {this->io};
    std::unordered_map<std::string, std::shared_ptr<ICommandHandler>> commandHandlers;
    std::map<int, std::shared_ptr<CommandTracker>> commandTrackers;
    int nextCommandId = 0;
    std::thread receiveThread;
    bool stopReceiveThread = false;
    QueueEcsSerialized m_serializedEcsDataQueue;
    int clientId;
    int roomId;
    std::string name;
    int ping;
  };
} // namespace Client
