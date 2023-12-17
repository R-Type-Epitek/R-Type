//
// Created by Alexandre Decobert on 17/12/2023.
//

#include "Game.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "R-TYPE") {
  mediator = std::make_shared<Mediator>();
  controller = std::make_unique<Controller>(mediator);
  mediator->Init();
  controller->init(window);
}

Game::~Game() {
  window.close();
}

void Game::run() {
  sf::Sprite currentSprite =
  mediator->getComponent<sf::Sprite>(controller->getControllerId()); if
  (currentSprite.getTexture() == nullptr) std::cout << "Texture is null" <<
  std::endl; ComponentRType::Transform transform =
  mediator->getComponent<ComponentRType::Transform>(controller->getControllerId());
  std::cout << currentSprite.getPosition().x  << std::endl;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::White);
    //currentSprite.setPosition(transform.position.x, transform.position.y);
    //window.draw(currentSprite);
    window.display();
  }
}