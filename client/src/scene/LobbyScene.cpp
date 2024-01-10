//
// Created by edouard on 12/21/23.
//

#include "scene/LobbyScene.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "network/system/Network.hpp"
#include "spdlog/spdlog.h"

namespace Client
{

  LobbyScene::LobbyScene(Network& network)
    : m_network {network}
  {
    initRegistries();
    initEntities();
  }

  void LobbyScene::initRegistries()
  {
    GameEngine::Scene::SimpleScene::initRegistries();
    initCustomSystem();
  }

  void LobbyScene::initCustomSystem()
  {
    using NetworkSystem = Client::System::KeyboardInputHandler;
    GameEngine::ECS::Signature signature;
    m_ecsRegistry->registerSystem<NetworkSystem>();
    signature.set(m_ecsRegistry->getComponentType<ComponentRType::Displayable>());
    m_ecsRegistry->setSystemSignature<NetworkSystem>(signature);
  }

  void LobbyScene::initEntities()
  {
    auto enttBackground = m_ecsRegistry->createEntity();
    m_entities.push_back(enttBackground);
    m_ecsRegistry->addComponent(
      enttBackground,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/lobby/bg.png")));

    auto enttJoinButton = m_ecsRegistry->createEntity();
    m_entities.push_back(enttJoinButton);
    m_ecsRegistry->addComponent(enttJoinButton, ComponentRType::Transform());
    m_ecsRegistry->addComponent(enttJoinButton, ComponentRType::Position(963, 720));
    m_ecsRegistry->addComponent(enttJoinButton, ComponentRType::Clickable());
    m_ecsRegistry->addComponent(
      enttJoinButton,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/lobby/accept_button.png")));

    auto enttReturnButton = m_ecsRegistry->createEntity();
    m_entities.push_back(enttReturnButton);
    m_ecsRegistry->addComponent(enttReturnButton, ComponentRType::Transform());
    m_ecsRegistry->addComponent(enttReturnButton, ComponentRType::Clickable());
    m_ecsRegistry->addComponent(enttReturnButton, ComponentRType::Position(803, 720));
    m_ecsRegistry->addComponent(
      enttReturnButton,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/lobby/return_button.png")));

    auto enttEscapeButton = m_ecsRegistry->createEntity();
    m_entities.push_back(enttEscapeButton);
    m_ecsRegistry->addComponent(enttEscapeButton, ComponentRType::Transform());
    m_ecsRegistry->addComponent(enttEscapeButton, ComponentRType::Position(1182, 270));
    m_ecsRegistry->addComponent(enttEscapeButton, ComponentRType::Clickable());
    m_ecsRegistry->addComponent(
      enttEscapeButton,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/lobby/escape_button.png")));

    m_entityFactory = std::make_unique<GameEngine::Entity::EntityFactory>(m_entities, *m_ecsRegistry);
  }

} // namespace Client
