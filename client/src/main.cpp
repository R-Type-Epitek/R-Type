//
// Created by edouard on 12/12/23.
//
#include "Game.hpp"

#include "Client.hpp"
#include "spdlog/spdlog.h"

//int main() {
//  spdlog::set_level(spdlog::level::debug);
//  Client::Client client = Client::Client();
//
//  client.initNetwork();
//  client.initGUI();
//  client.initScenes();
//  client.link();
//  client.run();
//};

int main() {
  Game game;
  game.run();
  return 0;
}
