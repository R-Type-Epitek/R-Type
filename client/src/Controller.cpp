//
// Created by Alexandre Decobert on 16/12/2023.
//

#include "Controller.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "gameEngine/system/Animation.hpp"
#include "gameEngine/system/Physics.hpp"
#include <iostream>

Controller::Controller() {
  this->registry = std::make_shared<GameEngine::ECS::Registry>();
  init();
}

void Controller::setClientId(int identifier) { this->id = identifier; }

int Controller::getClientId() const { return this->id; }

void Controller::setRoomId(int identifier) { this->room_id = identifier; }

int Controller::getRoomId() const { return this->room_id; }

void Controller::init() {
  initCRegister();
  initSRegister();
}

void Controller::initCRegister() {
  registry->registerComponent<ComponentRType::Sprite>();
  registry->registerComponent<ComponentRType::Transform>();
  registry->registerComponent<ComponentRType::Gravity>();
}

void Controller::initSRegister() {
  GameEngine::ECS::Signature signature_physics;
  GameEngine::ECS::Signature signature_animation;
  registry->registerSystem<GameEngine::ECS::Physics>();
  registry->registerSystem<GameEngine::System::Animation>();
  signature_physics.set(registry->getComponentType<ComponentRType::Gravity>());
  signature_physics.set(registry->getComponentType<ComponentRType::Transform>());
  signature_animation.set(registry->getComponentType<ComponentRType::Sprite>());
  signature_animation.set(registry->getComponentType<ComponentRType::Transform>());
  registry->setSystemSignature<GameEngine::ECS::Physics>(signature_physics);
  registry->setSystemSignature<GameEngine::System::Animation>(signature_animation);
}
