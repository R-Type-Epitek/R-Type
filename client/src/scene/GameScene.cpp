//
// Created by raphael on 12/21/23.
//

#include "scene/GameScene.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "spdlog/spdlog.h"

namespace Client {

GameScene::GameScene() {
  initRegistry();
  initEntities();
}

GameEngine::ECS::Registry& GameScene::getECS() { return *m_registry; }

void GameScene::initRegistry() {
  auto builder = GameEngine::Builder::RegistryBuilder();
  // Components
  builder.registerComponent<ComponentRType::Sprite>();
  builder.registerComponent<ComponentRType::Transform>();
  builder.registerComponent<ComponentRType::Gravity>();
  // Systems
  builder.buildSystemPhysics();
  builder.buildSystemAnimation();
  builder.buildSystemRenderer();
  builder.buildSystemKeyboard();
  m_registry = builder.getResult();
}

void GameScene::initEntities() {
  //  TODO generate entities from network
  auto entt = m_registry->createEntity();
  m_entities.push_back(entt);
  m_registry->addComponent(entt, ComponentRType::Gravity{Vec3{1}});
  m_registry->addComponent(entt, ComponentRType::Transform{{0, 0}});
  m_registry->addComponent(entt, ComponentRType::Sprite{});

  auto entt2 = m_registry->createEntity();
  m_entities.push_back(entt2);
  m_registry->addComponent(entt2, ComponentRType::Gravity{Vec3{1}});
  m_registry->addComponent(entt2, ComponentRType::Transform{{0, 0}});
  m_registry->addComponent(entt2, ComponentRType::Sprite{});

  auto entt1 = m_registry->createEntity();
  m_entities.push_back(entt1);
  m_registry->addComponent(entt1, ComponentRType::Sprite{});
}

}  // namespace Client
