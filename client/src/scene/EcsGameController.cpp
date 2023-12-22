//
// Created by Alexandre Decobert on 16/12/2023.
//

#include "scene/EcsGameController.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "gameEngine/system/Animation.hpp"
#include "gameEngine/system/Physics.hpp"

namespace Client::ECS {
EcsGameController::EcsGameController() { init(); }

void EcsGameController::setClientId(int identifier) { m_id = identifier; }

int EcsGameController::getClientId() const { return m_id; }

void EcsGameController::setRoomId(int identifier) { m_roomId = identifier; }

int EcsGameController::getRoomId() const { return m_roomId; }

void EcsGameController::init() {
  initCRegister();
  initSRegister();

  auto entt = m_registry.createEntity();
  m_entities.push_back(entt);
  m_registry.addComponent(entt, ComponentRType::Gravity{Vec3{1}});
  m_registry.addComponent(entt, ComponentRType::Transform{{0, 0}});
}

void EcsGameController::initCRegister() {
  m_registry.registerComponent<ComponentRType::Sprite>();
  m_registry.registerComponent<ComponentRType::Transform>();
  m_registry.registerComponent<ComponentRType::Gravity>();
}

void EcsGameController::initSRegister() {
  GameEngine::ECS::Signature signature_physics;
  m_registry.registerSystem<GameEngine::ECS::Physics>();
  signature_physics.set(m_registry.getComponentType<ComponentRType::Gravity>());
  signature_physics.set(m_registry.getComponentType<ComponentRType::Transform>());
  m_registry.setSystemSignature<GameEngine::ECS::Physics>(signature_physics);

  GameEngine::ECS::Signature signature_animation;
  m_registry.registerSystem<GameEngine::System::Animation>();
  signature_animation.set(m_registry.getComponentType<ComponentRType::Sprite>());
  signature_animation.set(m_registry.getComponentType<ComponentRType::Transform>());
  m_registry.setSystemSignature<GameEngine::System::Animation>(signature_animation);
}

GameEngine::ECS::Registry& EcsGameController::getECS() { return m_registry; }

}  // namespace Client::ECS