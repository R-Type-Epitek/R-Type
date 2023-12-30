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

namespace Server::Game
{
  void RtypeScene::initRegistry()
  {
    auto builder = GameEngine::Builder::RegistryBuilder();
    // Components
    builder.registerComponent<ComponentRType::Sprite>();
    builder.registerComponent<ComponentRType::Transform>();
    builder.registerComponent<ComponentRType::Gravity>();
    builder.registerComponent<ComponentRType::MetaData>();
    // Systems
    builder.buildSystemPhysics();
    builder.buildSystemAnimation();
    builder.buildSystemRenderer();
    builder.buildSystemKeyboard();
    m_registry = builder.getResult();
  }

  void RtypeScene::initEntities()
  {
    //  TODO load from config file or other https://vcpkg.io/en/packages
    auto entt = m_registry->createEntity();
    m_entities.push_back(entt);
    m_registry->addComponent(entt, ComponentRType::Gravity {Vec3 {1}});
    m_registry->addComponent(entt, ComponentRType::Transform {{0, 0}});
    m_registry->addComponent(entt, ComponentRType::Sprite {});

    auto entt2 = m_registry->createEntity();
    m_entities.push_back(entt2);
    m_registry->addComponent(entt2, ComponentRType::Gravity {Vec3 {1}});
    m_registry->addComponent(entt2, ComponentRType::Transform {{0, 0}});
    m_registry->addComponent(entt2, ComponentRType::Sprite {});

    auto entt1 = m_registry->createEntity();
    m_entities.push_back(entt1);
    m_registry->addComponent(entt1, ComponentRType::MetaData {"test send components data"});
  }

  GameEngine::ECS::Registry& RtypeScene::getECS()
  {
    return *m_registry;
  }

} // namespace Server::Game::Rtype