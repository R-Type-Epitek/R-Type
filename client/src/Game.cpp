//
// Created by Alexandre Decobert on 17/12/2023.
//

#include "Game.hpp"
#include "logic/SystemLogic.hpp"
#include "component/Gravity.hpp"
#include "component/Transform.hpp"
#include "component/Sprite.hpp"
#include "system/Physics.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "R-Type") {
  initPlayer(window);
}

void Game::initPlayer(sf::RenderWindow& window) {
  Entity player = mediator->createEntity();
  entities.push_back(player);
  sf::Texture texture;
  assert(texture.loadFromFile("assets/unknown.png") && "Texture not found");
  sf::Sprite sprite;
  sprite.setTexture(texture);
  float width = 60.0f;
  float height = 60.0f;
  sf::Vector2u texture_size = texture.getSize();
  float factor_x = width / texture_size.x;
  float factor_y = height / texture_size.y;
  sprite.setScale(factor_x, factor_y);
  float posX = (window.getSize().x / 2.0f) - (width / 2.0f);
  float posY = (window.getSize().y / 2.0f) - (height / 2.0f);
  sprite.setPosition(posX, posY);
  ComponentRType::Transform transform;
  transform.position.x = posX;
  transform.position.y = posY;
  mediator->addComponent(player, ComponentRType::Sprite());
  mediator->addComponent(player, ComponentRType::Gravity{Vec3{0}});
  mediator->addComponent(player, ComponentRType::Transform(transform));
}

Game::~Game() {
  window.close();
}

void Game::run() {
  SystemLogic systemLogic;
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