///*
//** EPITECH PROJECT, 2023
//** R-Type
//** File description:
//** UDPServer
//*/

#pragma once

#include "Client.hpp"
#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

namespace Network
{
    class UDPServer {
        public:
            UDPServer(boost::asio::io_context &io, int port);
            ~UDPServer();

        protected:
        private:
            boost::asio::ip::udp::socket socket;
            std::vector<Network::Client> clients;
            boost::array<char, 1024> recv_buffer{};
            boost::asio::ip::udp::endpoint remote_endpoint;

            void handle_receive(
                const boost::system::error_code &error,
                std::size_t bytes_transferred
            );
            void send_to_all(const std::string &message);
            void send_to_client(const std::string &message, int id);
            void start_receive();
            void process_message(
                std::string message,
                std::size_t bytes_transferred
            );
            void handle_message_from_client(
                std::string message,
                std::size_t bytes_transferred,
                int id
            );
            void handle_message_from_guest(
                std::string message,
                std::size_t bytes_transferred
            );
    };
}
