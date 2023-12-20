//
// Created by Alexandre Decobert on 17/12/2023.
//

#include "Game.hpp"
#include "component/Gravity.hpp"
#include "component/Sprite.hpp"
#include "component/Transform.hpp"
#include "constants/constants.hpp"
#include "logic/SystemLogic.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "R-Type") {}

void Game::initPlayer(sf::RenderWindow& window) {
  Entity player = mediator->createEntity();
  sf::Texture* texture = new sf::Texture();
  assert(texture->loadFromFile("assets/unknown.png") && "Texture not found");
  ComponentRType::Sprite sprite_component;
  sprite_component.texture = texture;
  entities.push_back(player);
  float width = 60.0f;
  float height = 60.0f;
  sf::Vector2u texture_size = texture->getSize();
  float factor_x = width / texture_size.x;
  float factor_y = height / texture_size.y;
  sprite_component.object.setScale(factor_x, factor_y);
  float posX = (window.getSize().x / 2.0f) - (width / 2.0f);
  float posY = (window.getSize().y / 2.0f) - (height / 2.0f);
  sprite_component.object.setPosition(posX, posY);
  ComponentRType::Transform transform;
  transform.position.x = posX;
  transform.position.y = posY;
  mediator->addComponent(player, ComponentRType::Sprite(sprite_component));
  mediator->addComponent(player, ComponentRType::Gravity{Vec3{1}});
  mediator->addComponent(player, ComponentRType::Transform(transform));
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
