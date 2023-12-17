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
  /*
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
*/
  std::bitset<MAX_COMPONENTS> mask;
  mask.set(mediator->getComponentType<sf::Sprite>());
  mask.set(mediator->getComponentType<ComponentRType::Transform>());
  mask.set(mediator->getComponentType<ComponentRType::Gravity>());
  std::bitset<MAX_COMPONENTS> mask2;
  mask2.set(mediator->getComponentType<ComponentRType::Transform>());
  mask2.set(mediator->getComponentType<ComponentRType::Gravity>());
  if ((mask & mask2) == mask2) std::cout << "Mask is equal" <<
  std::endl; else std::cout << "Mask is not equal" << std::endl;
}