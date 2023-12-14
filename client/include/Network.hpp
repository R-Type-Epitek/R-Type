//
// Created by Xavier VINCENT on 14/12/2023.
//

#pragma once

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

// Default values
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "4242"

// Errors
#define NO_CLIENT_ID "You must connect to the server first"

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
