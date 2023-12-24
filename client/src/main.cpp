//
// Created by edouard on 12/12/23.
//
#include "Client.hpp"
#include "spdlog/spdlog.h"

int main() {
  spdlog::set_level(spdlog::level::debug);
  Client::Client client = Client::Client();

  client.initNetwork();
  client.initScenes();
  client.initGUI();
  client.link();
  client.run();
};
