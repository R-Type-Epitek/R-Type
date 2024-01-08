//
// Created by edouard on 12/21/23.
//

#include "scene/LobbyScene.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "network/system/Keyboard.hpp"
#include "spdlog/spdlog.h"

namespace Client
{

  LobbyScene::LobbyScene(Network& network)
    : m_network {network}
  {
    initRegistry();
    initEntities();
  }

  GameEngine::ECS::Registry& LobbyScene::getECS()
  {
    return *m_registry;
  }

  GameEngine::Entity::EntityFactory& LobbyScene::getEntityFactory()
  {
    return *m_entityFactory;
  }

  void LobbyScene::initRegistry()
  {
    auto builder = GameEngine::Builder::RegistryBuilder();

    // Components
    builder.registerAllMandatoryComponent();

    // Systems
    builder.buildSystemPhysics();
    builder.buildSystemMove();
    builder.buildSystemAnimation();
    builder.buildSystemRenderer();
    builder.buildSystemKeyboard();
    builder.buildSystemEcsSerializer();
    m_registry = builder.getResult();

    // Custom client System
    initCustomSystem();
  }

  void LobbyScene::initCustomSystem()
  {
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<System::Network::Keyboard>();
    //    System components
    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    m_registry->setSystemSignature<System::Network::Keyboard>(signature);
  }

  void LobbyScene::initEntities()
  {
    auto enttBackground = m_registry->createEntity();
    m_entities.push_back(enttBackground);
    m_registry->addComponent(
      enttBackground,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/lobby/bg.png")));

    auto enttJoinButton = m_registry->createEntity();
    m_entities.push_back(enttJoinButton);
    m_registry->addComponent(enttJoinButton, ComponentRType::Transform());
    m_registry->addComponent(enttJoinButton, ComponentRType::Position(963, 720));
    m_registry->addComponent(enttJoinButton, ComponentRType::Clickable());
    m_registry->addComponent(
      enttJoinButton,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/lobby/accept_button.png")));

    auto enttReturnButton = m_registry->createEntity();
    m_entities.push_back(enttReturnButton);
    m_registry->addComponent(enttReturnButton, ComponentRType::Transform());
    m_registry->addComponent(enttReturnButton, ComponentRType::Clickable());
    m_registry->addComponent(enttReturnButton, ComponentRType::Position(803, 720));
    m_registry->addComponent(
      enttReturnButton,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/lobby/return_button.png")));

    auto enttEscapeButton = m_registry->createEntity();
    m_entities.push_back(enttEscapeButton);
    m_registry->addComponent(enttEscapeButton, ComponentRType::Transform());
    m_registry->addComponent(enttEscapeButton, ComponentRType::Position(1182, 270));
    m_registry->addComponent(enttEscapeButton, ComponentRType::Clickable());
    m_registry->addComponent(
      enttEscapeButton,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/lobby/escape_button.png")));

    m_entityFactory = std::make_unique<GameEngine::Entity::EntityFactory>(m_entities, *m_registry);
  }
} // namespace Client
