/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** UDPServer
*/

#pragma once

#include "Constants.hpp"
#include "Client.hpp"
#include "Room.hpp"

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
            boost::array<char, 1024> recv_buffer{};
            boost::asio::ip::udp::endpoint remote_endpoint;
            std::vector<Network::Room> rooms;

            void init_server(int port);
            void init_rooms(int count);
            void handle_receive(
                const boost::system::error_code &error,
                std::size_t bytes_transferred
            );
            void send_to_all(const boost::asio::const_buffer &buffer);
            void send_to_client(
                const boost::asio::const_buffer &buffer,
                int id
            );
            void start_receive();
            void process_message(const boost::asio::const_buffer &buffer);
            Response create_response(
                int client_id,
                const std::string& command,
                const std::string& status_message,
                int status
            );
            void send_response_and_log(const Response& response);
            void hello_command(Message *message);
            void name_command(Message *message);
            void join_command(Message *message);
    };
}
