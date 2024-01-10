//
// Created by raphael on 12/21/23.
//

#include "scene/Lobby.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "gameEngine/system/InputCatcher.hpp"
#include "gameEngine/event/Events.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "spdlog/spdlog.h"

namespace Rtype::Scene
{

  Lobby::Lobby(Controller::GraphicController &controller)
    : m_controller(controller)
  {
    spdlog::info("Lobby scene created");
  }

  void Lobby::initRegistries()
  {
    SimpleScene::initRegistries();
  }

  void Lobby::initEntities()
  {
    SimpleScene::initEntities();

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
  }

  void Lobby::initEvents()
  {
    SimpleScene::initEvents();
  }

  void Lobby::onUpdate(size_t df)
  {
    SimpleScene::onUpdate(df);
    auto &ecsRegistry = getEcsRegistry();
    {
      auto system = ecsRegistry.getSystem<GameEngine::System::InputCatcher>();
      system->update(getEventRegistry(), m_controller.getRenderer());
    }
    {
      auto system = ecsRegistry.getSystem<GameEngine::System::Renderer>();
      system->update(ecsRegistry, m_controller.getRenderer());
    }
  }
}
