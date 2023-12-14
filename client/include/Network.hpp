//
// Created by Xavier VINCENT on 14/12/2023.
//

#pragma once

#include "Constants.hpp"

namespace Client
{
    class Network {
        public:
            Network(
              boost::asio::io_context &io,
              std::string ip,
              std::string port
            );
            ~Network();
            void send(const boost::asio::const_buffer &buffer);
            void send_message(
                const std::string& command,
                const char* data,
                size_t dataSize
            );
            Response* receive_and_validate_response(
                const std::string& expectedCommand
            );
            void connect_to_server();
            void send_name(std::string name);
            void join_room(int room_id);
            void setClientId(int id);
            int getClientId() const;
            void setRoomId(int id);
            int getRoomId() const;
            void setName(std::string name);
            std::string getName() const;

        protected:
        private:
            boost::asio::io_context io;
            boost::asio::ip::udp::endpoint receiver_endpoint;
            boost::asio::ip::udp::socket socket;
            int client_id;
            int room_id;
            std::string name;
    };
}
