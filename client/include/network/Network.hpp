//
// Created by Xavier VINCENT on 14/12/2023.
//

#pragma once
#include "Constants.hpp"
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
#include <string>

namespace Client
{
  class Network {
   public:
    Network(std::string ip, std::string port);
    ~Network();
    void registerCommandHandlers();
    std::shared_ptr<ICommandHandler> getCommandHandler(std::string const &name);
    void send(boost::asio::const_buffer const &buffer);
    void sendMessage(std::string const &command, char const data[] = nullptr, int dataSize = 0);
    void sendResponse(
      std::string const &command,
      std::string const &statusMessage,
      char const data[] = nullptr,
      int dataSize = 0,
      int status = RES_SUCCESS);
    void startReceive();
    void onReceive(boost::system::error_code const &error, std::size_t bytesTransferred);
    void onServerResponse(Response *response);
    void onServerMessage(Message *message);

    void onCheckConnectionMessage(Message *message);

    void setClientId(int id);
    int getClientId() const;
    void setRoomId(int id);
    int getRoomId() const;
    void setName(std::string name);
    std::string getName() const;
    void setRemoteEndpoint(std::string &ip, std::string &port);
    boost::asio::ip::udp::endpoint getRemoteEndpoint() const;

    // commands
    template<typename T, typename Func>
    void executeCommand(const std::string &commandName, Func action);
    void connectToServer();
    void updateName(std::string name);
    void joinRoom(int roomId);
    void sendKey(std::string key);
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
    int clientId;
    int roomId;
    std::string name;
  };
} // namespace Client
