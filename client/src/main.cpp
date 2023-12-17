//
// Created by edouard on 12/12/23.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Controller.hpp"
#include "ecs/Mediator.hpp"
#include "Game.hpp"
#include <memory>
#include "network/Network.hpp"

int main() {
  Game game;
  game.run();
  return 0;
}
