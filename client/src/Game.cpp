//
// Created by Alexandre Decobert on 17/12/2023.
//

#include <iostream>
#include "Game.hpp"
#include "logic/SystemLogic.hpp"
#include "component/Gravity.hpp"
#include "component/Transform.hpp"
#include "constants/constants.hpp"
#include "component/Sprite.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "R-Type") {}

void Game::initPlayer(sf::RenderWindow& window)
{
  Entity player = mediator->createEntity();
  ComponentRType::Sprite sprite_component;
  ComponentRType::Transform transform;
  entities.push_back(player);

  sf::Texture texture;
  assert(texture.loadFromFile("assets/unknown.png") && "Texture not found");
  sprite_component.object.setTexture(texture);
  float width = 60.0f;
  float height = 60.0f;
  sf::Vector2u texture_size = texture.getSize();
  float factor_x = width / texture_size.x;
  float factor_y = height / texture_size.y;
  sprite_component.object.setScale(factor_x, factor_y);
  float posX = (window.getSize().x / 2.0f) - (width / 2.0f);
  float posY = (window.getSize().y / 2.0f) - (height / 2.0f);
  sprite_component.object.setPosition(posX, posY);

  transform.position.x = posX;
  transform.position.y = posY;
  // sprite
  mediator->addComponent(player, ComponentRType::Sprite(sprite_component));
  mediator->addComponent(player, ComponentRType::Gravity{Vec3{2}});
  mediator->addComponent(player, ComponentRType::Transform(transform));
}

Game::~Game() {
  window.close();
}

void Game::run() {
  initPlayer(window);

  SystemLogic systemLogic;

  // get sprite
  auto& sprite1 = mediator->getComponent<ComponentRType::Sprite>(0).object;

  std::cout << "Sprite1 position: " << sprite1.getPosition().x << ", " << sprite1.getPosition().y << std::endl;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::White);
    // systemLogic.launchSystem(mediator, entities, window);
    // display sprite
    window.draw(sprite1);
    window.display();
  }
}