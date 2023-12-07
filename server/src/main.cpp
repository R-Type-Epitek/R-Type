///*
//** EPITECH PROJECT, 2023
//** R-Type
//** File description:
//** Server Main
//*/
//
#include "network/UDPServer.hpp"

int main(int argc, char **argv)
{
    try {
        if (argc != 2) {
            std::cerr << "Usage: network <port>" << std::endl;
            return 1;
        }
        boost::asio::io_context io;
        Network::UDPServer server(io, std::atoi(argv[1]));

        io.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

