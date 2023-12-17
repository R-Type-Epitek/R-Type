//
// Created by Alexandre Decobert on 17/12/2023.
//

#include "Game.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "R-TYPE") {
  mediator = std::make_shared<Mediator>();
  controller = std::make_unique<Controller>(mediator);
  mediator->Init();
  controller->init(window);
  entities.push_back(mediator->createEntity());
}

Game::~Game() {
  window.close();
}

void Game::run() {
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::White);
    window.display();
  }
}