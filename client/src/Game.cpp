//
// Created by Alexandre Decobert on 17/12/2023.
//

#include "Game.hpp"
#include "component/Gravity.hpp"
#include "component/Sprite.hpp"
#include "component/Transform.hpp"
#include "constants/constants.hpp"
#include "logic/SystemLogic.hpp"
#include "component/ComponentBuilder.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "R-Type") {}

void Game::initPlayer(sf::RenderWindow& window) {
  Entity player = mediator->createEntity();
  entities.push_back(player);

  ComponentBuilder().createEntity(
      *mediator,
      player,
      ComponentRType::Sprite{},
      ComponentRType::Gravity{Vec3{1}},
      ComponentRType::Transform{{0, 0}}
  );
}

Game::~Game() { window.close(); }

void Game::run() {
  SystemLogic systemLogic;
  initPlayer(window);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::White);
    systemLogic.launchSystem(mediator, entities, window);
    window.display();
  }
}
