//
// Created by Xavier VINCENT on 14/12/2023.
//

#pragma once

#include "Constants.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>


namespace Client
{
    class Network {
        public:
            Network(std::string ip, std::string port);
            ~Network() = default;
            void send(const boost::asio::const_buffer &buffer);
            void sendMessage(
                const std::string& command,
                const char* data,
                size_t dataSize
            );
            Response* receiveAndValidateResponse(
                const std::string& expectedCommand
            );
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
            void setEndpoint(
                std::string &ip,
                std::string &port
            );

        protected:
        private:
            boost::asio::io_context io;
            boost::asio::ip::udp::endpoint receiverEndpoint;
            boost::asio::ip::udp::socket socket{this->io};
            int clientId;
            int roomId;
            std::string name;
    };
}
