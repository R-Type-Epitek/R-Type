/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** UDPServer
*/

#pragma once

#include "Client.hpp"
#include "Room.hpp"
#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#define DEFAULT_PORT 4242
#define DEFAULT_ROOM_SIZE 4
#define NUMBER_OF_ROOMS 4

// Commands
#define HELLO_COMMAND "/hello"
#define NAME_COMMAND "/name"
#define JOIN_COMMAND "/join"

struct MessageHeader {
  int client_id;
  char command[32];
  uint32_t dataLength;
};

struct Message {
  MessageHeader header;
  char data[];
};

struct ResponseHeader {
  int client_id;
  char command[32];
  uint32_t dataLength;
  int status;
  char status_message[128];
};

struct Response {
  ResponseHeader header;
  char data[];
};

struct SendNameData {
  char name[32];
};

struct JoinRoomData {
  int room_id;
};

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
            void hello_command(Message *message);
            void name_command(Message *message);
            void join_command(Message *message);
    };
}
