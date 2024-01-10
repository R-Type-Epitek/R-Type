//
// Created by raphael on 12/21/23.
//

#include "scene/Welcome.hpp"
#include "gameEngine/system/NetworkEventPusher.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "gameEngine/system/Move.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "spdlog/spdlog.h"

namespace Rtype::Scene
{

  Welcome::Welcome(Controller::GraphicController &controller)
    : m_controller(controller)
  {
    spdlog::info("Welcome scene created");
  }

  void Welcome::initRegistries()
  {
    SimpleScene::initRegistries();
  }

  void Welcome::initEntities()
  {
    SimpleScene::initEntities();
    auto enttBackground = m_ecsRegistry->createEntity();
    m_entities.push_back(enttBackground);
    m_ecsRegistry->addComponent(
      enttBackground,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/welcome/bg.jpg")));

    auto enttButton = m_ecsRegistry->createEntity();
    m_entities.push_back(enttButton);
    m_ecsRegistry->addComponent(
      enttButton,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/welcome/rtype_button.jpg")));
    m_ecsRegistry->addComponent(enttButton, ComponentRType::Transform());
    m_ecsRegistry->addComponent(enttButton, ComponentRType::Position(615, 480));
    m_ecsRegistry->addComponent(enttButton, ComponentRType::Clickable(615, 480, 690, 120));
  }

  void Welcome::initEvents()
  {
    SimpleScene::initEvents();

    auto moveSystem = m_ecsRegistry->getSystem<GameEngine::System::Move>();
    m_eventRegistry->subscribe<GameEngine::Event::EventKeyboardInput>(moveSystem);
  }

  void Welcome::onUpdate(size_t df)
  {
    SimpleScene::onUpdate(df);
    auto &ecsRegistry = getEcsRegistry();

    {
      auto system = ecsRegistry.getSystem<GameEngine::System::Move>();
      system->updateClient(ecsRegistry);
    }
    {
      auto system = ecsRegistry.getSystem<GameEngine::System::Renderer>();
      system->update(ecsRegistry, m_controller.getRenderer());
    }
  }
} // namespace Rtype::Scene
