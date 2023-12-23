//
// Created by Xavier VINCENT on 14/12/2023.
//

#pragma once

#include "Constants.hpp"
#include "gameEngine/network/Commands.hpp"
#include "gameEngine/network/Messages.hpp"
#include "gameEngine/network/Responses.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <string>

namespace Client {
class Network {
 public:
  Network(std::string ip, std::string port);
  ~Network() = default;
  void send(boost::asio::const_buffer const& buffer);
  void sendMessage(std::string const& command, char const* data, size_t dataSize);
  Response* receiveAndValidateResponse(std::string const& expectedCommand);
  void connectToServer();
  void updateName(std::string name);
  void joinRoom(int roomId);
  void sendKey(std::string key);
  void startGame(int roomId);
  void setClientId(int id);
  int getClientId() const;
  void setRoomId(int id);
  int getRoomId() const;
  void setName(std::string name);
  std::string getName() const;
  void setEndpoint(std::string& ip, std::string& port);

 private:
  boost::asio::io_context io;
  boost::asio::ip::udp::endpoint receiverEndpoint;
  boost::asio::ip::udp::socket socket{this->io};
  int clientId;
  int roomId;
  std::string name;
};
}  // namespace Client
