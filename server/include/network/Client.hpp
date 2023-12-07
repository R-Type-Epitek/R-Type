///*
//** EPITECH PROJECT, 2023
//** R-Type
//** File description:
//** Client
//*/

#pragma once
#include <boost/asio.hpp>

namespace Network
{
    class Client {
        public:
            Client();
            ~Client();
            boost::asio::ip::udp::endpoint getEndpoint() const;
            void setEndpoint(boost::asio::ip::udp::endpoint endpoint);
            int getId() const;
            void setId(int id);
            std::string getName() const;
            void setName(std::string name);

        protected:
        private:
            boost::asio::ip::udp::endpoint endpoint;
            int id;
            std::string name;
    };
}
