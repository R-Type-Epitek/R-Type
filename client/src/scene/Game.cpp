//
// Created by raphael on 12/21/23.
//

#include "RTypeClient.hpp"
#include "scene/GameScene.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "network/system/Keyboard.hpp"
#include "spdlog/spdlog.h"

namespace Client
{

  GameScene::GameScene(Network& network)
    : m_network {network}
  {
    initRegistry();
    initEntities();
  }

  GameEngine::ECS::Registry& GameScene::getECS()
  {
    return *m_registry;
  }

  void GameScene::initRegistry()
  {
    auto builder = GameEngine::Builder::RegistryBuilder();

    // Components
    builder.registerComponent<ComponentRType::Sprite>();
    builder.registerComponent<ComponentRType::Transform>();
    builder.registerComponent<ComponentRType::Gravity>();
    builder.registerComponent<ComponentRType::MetaData>();
    builder.registerComponent<ComponentRType::MetaDataTest>();

    // Systems
    builder.buildSystemPhysics();
    builder.buildSystemAnimation();
    builder.buildSystemRenderer();
    builder.buildSystemKeyboard();
    m_registry = builder.getResult();

    // Custom client System
    initCustomSystem();
  }

  void GameScene::initCustomSystem()
  {
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<Client::System::Network::Keyboard>();
    //  System components
    signature.set(m_registry->getComponentType<ComponentRType::Sprite>());
    m_registry->setSystemSignature<Client::System::Network::Keyboard>(signature);
  }

  void GameScene::initEntities()
  {
    //  TODO generate entities from network
    auto entt = m_registry->createEntity();
    m_entities.push_back(entt);
    m_registry->addComponent(entt, ComponentRType::Gravity {Vec3 {1}});
    m_registry->addComponent(entt, ComponentRType::Transform {{0, 0}});
    m_registry->addComponent(entt, ComponentRType::Sprite {});
    m_registry->addComponent(entt, ComponentRType::MetaData {"test entity 1"});
    m_registry->addComponent(entt, ComponentRType::MetaDataTest {"test entity 2", 2});

    auto entt2 = m_registry->createEntity();
    m_entities.push_back(entt2);
    m_registry->addComponent(entt2, ComponentRType::Gravity {Vec3 {1}});
    m_registry->addComponent(entt2, ComponentRType::Transform {{0, 0}});
    m_registry->addComponent(entt2, ComponentRType::Sprite {});

    auto entt1 = m_registry->createEntity();
    m_entities.push_back(entt1);
    m_registry->addComponent(entt1, ComponentRType::Sprite {});
    m_registry->addComponent(entt1, ComponentRType::MetaData {"test entity 2"});
    m_registry->addComponent(entt1, ComponentRType::MetaDataTest {"test entity 2", 2});
  }
} // namespace Client
