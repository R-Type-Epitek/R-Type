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
        boost::asio::io_context io;
        Network::UDPServer server(io, argv[1] ? std::stoi(argv[1]) : DEFAULT_PORT);

        io.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

