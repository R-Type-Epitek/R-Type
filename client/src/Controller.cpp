//
// Created by Alexandre Decobert on 16/12/2023.
//

#include "Controller.hpp"
#include "ecs/Mediator.hpp"
#include "component/Gravity.hpp"
#include "component/Transform.hpp"
#include "component/Sprite.hpp"
#include "system/Physics.hpp"
#include <iostream>

Controller::Controller() {
  mediator = std::make_shared<Mediator>();
  mediator->Init();
  this->mediator = mediator;
  init();
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

void Controller::init() {
  initCRegister();
  initSRegister();
}

void Controller::initCRegister() {
  mediator->registerComponent<ComponentRType::Sprite>();
  mediator->registerComponent<ComponentRType::Transform>();
  mediator->registerComponent<ComponentRType::Gravity>();
}

void Controller::initSRegister() {
  Signature signature_physics;
  Signature signature_animation;
  mediator->registerSystem<Physics>();
  signature_physics.set(mediator->getComponentType<ComponentRType::Gravity>());
  signature_physics.set(mediator->getComponentType<ComponentRType::Transform>());
  signature_animation.set(mediator->getComponentType<ComponentRType::Sprite>());
  signature_animation.set(mediator->getComponentType<ComponentRType::Transform>());
  mediator->setSystemSignature<Physics>(signature_physics);
}

