//
// Created by edouard on 12/12/23.
//

#include "Client.hpp"

#include <spdlog/spdlog.h>

int main(int const ac, char const *const av[])
{
  spdlog::set_level(spdlog::level::debug);
  std::string ip = DEFAULT_IP;
  std::string port = DEFAULT_PORT;
  if (ac == 3) {
    ip = av[1];
    port = av[2];
  }
  Client::Client client(ip, port);

  client.run();
};
