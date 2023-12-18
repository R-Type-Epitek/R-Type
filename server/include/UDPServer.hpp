//
// Created by Xavier VINCENT on 13/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"

namespace Network
{
    class UDPServer {
        public:
            UDPServer(boost::asio::io_context &io);
            UDPServer(boost::asio::io_context &io, int port);
            ~UDPServer();

        protected:
        private:
            boost::asio::ip::udp::socket socket;
            std::vector<Network::Client> clients;
            boost::array<char, 1024> recvBuffer{};
            boost::asio::ip::udp::endpoint remoteEndpoint;
            Network::ThreadSafeQueue<Message *> messageQueue;
            std::vector<std::thread> workers;
            std::vector<Network::Room> rooms;

            void initServer(int port);
            void initRooms(int count);
            void handleReceive(
                const boost::system::error_code &error,
                std::size_t bytesTransferred
            );
            void sendToAll(const boost::asio::const_buffer &buffer);
            void sendToClient(
                const boost::asio::const_buffer &buffer,
                int id
            );
            void startReceive();
            void processMessage(Message *message);
            void workerFunction();
            Response createResponse(
                int clientId,
                const std::string& command,
                const std::string& statusMessage,
                int status
            );
            void sendResponseAndLog(const Response& response);
            void helloCommand(Message *message);
            void nameCommand(Message *message);
            void joinCommand(Message *message);
            void keyCommand(Message *message);
    };
}
