//
// Created by Xavier VINCENT on 12/12/2023.
//

#include "RTypeNetwork.hpp"

int main(int argc, char **argv) {
    try {
        boost::asio::io_context io;
        boost::asio::io_context::work idleWork(io);
        Network::UDPServer server(
            io,
            argc > 1 ? std::stoi(argv[1]) : std::stoi(DEFAULT_PORT)
        );

        std::vector<std::thread> threads;
        int num_threads = std::thread::hardware_concurrency();
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([&io] { io.run(); });
        }

        for (auto &thread : threads) {
            thread.join();
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

