//
// Created by Xavier VINCENT on 13/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"

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
