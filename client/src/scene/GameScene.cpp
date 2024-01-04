//
// Created by raphael on 12/21/23.
//

#include "scene/GameScene.hpp"

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/asset/AssetManager.hpp"
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

  std::vector<GameEngine::ECS::Entity>& GameScene::getEntities()
  {
    return m_entities;
  }

  void GameScene::initRegistry()
  {
    auto builder = GameEngine::Builder::RegistryBuilder();

    // Components
    builder.registerAllMandatoryComponent();
    builder.registerComponent<ComponentRType::Displayable>();

    // Systems
    builder.buildSystemPhysics();
    builder.buildSystemAnimation();
    builder.buildSystemRenderer();
    builder.buildSystemKeyboard();
    builder.buildSystemEcsSerializer();
    m_registry = builder.getResult();

    // Custom client System
    initCustomSystem();
  }

  void GameScene::initCustomSystem()
  {
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<System::Network::Keyboard>();
    //  System components
    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    m_registry->setSystemSignature<System::Network::Keyboard>(signature);
  }

  void GameScene::initEntities()
  {
    namespace assetManager = GameEngine::Asset;

    auto entt2 = m_registry->createEntity();
    m_entities.push_back(entt2);
    m_registry->addComponent(entt2, ComponentRType::Gravity {});
    m_registry->addComponent(entt2, ComponentRType::Transform {});
    m_registry->addComponent(
      entt2,
      ComponentRType::Displayable(assetManager::getTexture("assets/sprites/r-typesheet23.gif")));
  }

} // namespace Client
