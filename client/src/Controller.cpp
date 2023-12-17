//
// Created by Alexandre Decobert on 16/12/2023.
//

#include "Controller.hpp"
#include "ecs/Mediator.hpp"
#include "component/Gravity.hpp"
#include "component/Transform.hpp"
#include "component/Sprite.hpp"
#include "system/Physics.hpp"
#include "system/Animation.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Controller::Controller(std::shared_ptr<Mediator>& mediator) {
  this->mediator = mediator;
}

void Controller::setClientId(int id) {
  this->id = id;
}

int Controller::getClientId() const {
  return this->id;
}

void Controller::setRoomId(int id) {
  this->room_id = id;
}

int Controller::getRoomId() const {
  return this->room_id;
}

void Controller::setControllerId(int id) {
  this->controller_id = id;
}

int Controller::getControllerId() const {
  return this->controller_id;
}

void Controller::init(sf::RenderWindow& window) {
  initCRegister();
  initSRegister();
  initPlayer(window);
}

void Controller::initCRegister() {
  mediator->registerComponent<sf::Sprite>();
  mediator->registerComponent<ComponentRType::Transform>();
  mediator->registerComponent<ComponentRType::Gravity>();
}

void Controller::initSRegister() {
  Signature signature_physics;
  Signature signature_animation;
  mediator->registerSystem<Physics>();
  //mediator->registerSystem<Animation>();
  signature_physics.set(mediator->getComponentType<ComponentRType::Gravity>());
  signature_physics.set(mediator->getComponentType<ComponentRType::Transform>());
  signature_animation.set(mediator->getComponentType<ComponentRType::Sprite>());
  signature_animation.set(mediator->getComponentType<ComponentRType::Transform>());
  mediator->setSystemSignature<Physics>(signature_physics);
  //mediator->setSystemSignature<Physics>(signature_animation);
}

void Controller::initPlayer(sf::RenderWindow& window) {
  Entity player = mediator->createEntity();
  this->controller_id = player;
  // Engine front
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
  // front end
  mediator->addComponent(player, sf::Sprite());
  ComponentRType::Transform transform;
  transform.position.x = posX;
  transform.position.y = posY;
  mediator->addComponent(player, ComponentRType::Transform(transform));
  mediator->addComponent(player, ComponentRType::Gravity{Vec3{0}});
  // move
}