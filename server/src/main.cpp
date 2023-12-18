//
// Created by Xavier VINCENT on 12/12/2023.
//

#include "RTypeNetwork.hpp"

int main(int argc, char **argv)
{
    try {
        boost::asio::io_context io;
        Network::UDPServer server(
            io,
            argc > 1
                ? std::stoi(argv[1])
                : std::stoi(DEFAULT_PORT)
        );

        io.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
