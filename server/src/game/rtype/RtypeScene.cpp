//
// Created by raphael on 12/22/23.
//

#include "game/rtype/RtypeScene.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"

namespace Server::Game
{
  void RtypeScene::initRegistry()
  {
    auto builder = GameEngine::Builder::RegistryBuilder();

    // Components
    builder.registerAllMandatoryComponent();
    builder.registerComponent<ComponentRType::Sprite>();

    // Systems
    builder.buildSystemPhysics();
    builder.buildSystemAnimation();
    builder.buildSystemRenderer();
    builder.buildSystemKeyboard();
    builder.buildSystemEcsSerializer();
    m_registry = builder.getResult();
  }

  void RtypeScene::initEntities()
  {
    auto entt = m_registry->createEntity();
    m_entities.push_back(entt);
    m_registry->addComponent(entt, ComponentRType::Gravity {Vec3 {1}});
    m_registry->addComponent(entt, ComponentRType::Transform {{0, 0}});
    m_registry->addComponent(entt, ComponentRType::MetaData {"test entity 1"});

    auto entt2 = m_registry->createEntity();
    m_entities.push_back(entt2);
    m_registry->addComponent(entt2, ComponentRType::Gravity {Vec3 {1}});
    m_registry->addComponent(entt2, ComponentRType::Transform {{0, 0}});
    m_registry->addComponent(entt2, ComponentRType::Sprite {});

    auto entt1N = m_registry->createEntity();
    m_entities.push_back(entt1N);
    m_registry->addComponent(entt1N, ComponentRType::MetaData {"test entity 1"});
    m_registry->addComponent(entt1N, ComponentRType::NetworkedEntity {1});

    auto entt2N = m_registry->createEntity();
    m_entities.push_back(entt2N);
    m_registry->addComponent(entt2N, ComponentRType::MetaData {"test entity 2"});
    m_registry->addComponent(entt2N, ComponentRType::NetworkedEntity {2});
  }

  GameEngine::ECS::Registry& RtypeScene::getECS()
  {
    return *m_registry;
  }

} // namespace Server::Game::Rtype