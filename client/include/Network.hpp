//
// Created by Xavier VINCENT on 14/12/2023.
//

#pragma once

#include "RTypeClient.hpp"

namespace Client
{
  class Network {
  public:
    Network(std::string ip, std::string port);
    ~Network();
    void send(boost::asio::const_buffer const &buffer);
    void sendMessage(
      std::string const &command,
      char const data[] = nullptr,
      int dataSize = 0);
    void sendResponse(
      std::string const &command,
      std::string const &statusMessage,
      char const data[] = nullptr,
      int dataSize = 0,
      int status = RES_SUCCESS);
    void startReceive();
    void onReceive(
      boost::system::error_code const &error,
      std::size_t bytesTransferred);
    void onServerResponse(Response *response);
    void onServerMessage(Message *message);

    /* ------------------ Server Message ----------------- */
    void connectToServer();
    void onConnectToServerResponse(Response *response);

    void updateName(std::string name);
    void onUpdateNameResponse(Response *response);

    void joinRoom(int roomId);
    void onJoinRoomResponse(Response *response);

    void sendKey(std::string key);
    void onSendKeyResponse(Response *response);

    void startGame(int roomId);
    void onStartGameResponse(Response *response);
    /* --------------------------------------------------- */

    void onCheckConnectionMessage(Message *message);

    void setClientId(int id);
    int getClientId() const;
    void setRoomId(int id);
    int getRoomId() const;
    void setName(std::string name);
    std::string getName() const;
    void setEndpoint(std::string &ip, std::string &port);

  protected:
  private:
    boost::asio::io_context io;
    boost::array<char, 1024> recvBuffer {};
    boost::asio::ip::udp::endpoint remoteEndpoint;
    boost::asio::ip::udp::socket socket {this->io};
    std::thread receiveThread;
    int clientId;
    int roomId;
    std::string name;
  };
} // namespace Client
