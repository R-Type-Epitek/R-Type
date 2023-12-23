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
            void send(const boost::asio::const_buffer &buffer);
            void sendMessage(
                const std::string& command,
                const char data[] = nullptr,
                int dataSize = 0
            );
            void sendResponse(
                const std::string& command,
                const std::string& statusMessage,
                const char data[],
                int dataSize,
                int status
            );
            void startReceive();
            void onReceive(
                const boost::system::error_code& error,
                std::size_t bytesTransferred
            );
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

            void onCheckConnectionMessage(Message* message);

            void setClientId(int id);
            int getClientId() const;
            void setRoomId(int id);
            int getRoomId() const;
            void setName(std::string name);
            std::string getName() const;
            void setEndpoint(
                std::string &ip,
                std::string &port
            );

        protected:
        private:
            boost::asio::io_context io;
            boost::array<char, 1024> recvBuffer{};
            boost::asio::ip::udp::endpoint remoteEndpoint;
            boost::asio::ip::udp::socket socket{this->io};
            std::thread receiveThread;
            int clientId;
            int roomId;
            std::string name;
    };
}
