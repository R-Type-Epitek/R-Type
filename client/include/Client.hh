//
// Created by edouard on 12/11/23.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <SFML/Window/Window.hpp>
#include <cstddef>
#include <iostream>

namespace client {
    using boost::asio::ip::udp;

    class ClientCommunication
    {
        public:
            ClientCommunication() = delete;
            ClientCommunication(std::size_t width, std::size_t height);
            ClientCommunication(std::size_t width, std::size_t height, std::string address, unsigned short port);
            ~ClientCommunication() = default;
            ClientCommunication(ClientCommunication const &to_copy) = delete;
            ClientCommunication(ClientCommunication &&to_move) = delete;
            ClientCommunication &operator=(ClientCommunication const &to_copy) = delete;
            ClientCommunication &operator=(ClientCommunication &&to_move) = delete;

            void send_event(sf::Event event);
        private:
            sf::RenderWindow window_;
            boost::asio::io_service io_service_;
    	    udp::endpoint receiver_endpoint_;
    	    udp::socket socket_;
            udp::endpoint sender_endpoint_;
    };
}
