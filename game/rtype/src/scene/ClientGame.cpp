//
// Created by raphael on 12/21/23.
//

#include "scene/ClientGame.hpp"
#include "gameEngine/system/Move.hpp"
#include "gameEngine/event/Events.hpp"
#include "spdlog/spdlog.h"

namespace Rtype::Scene
{

  ClientGame::ClientGame(SceneController::ClientGameController &controller)
    : m_controller(controller)
  {
    spdlog::info("ClientGame scene created");
  }

  void ClientGame::initRegistries()
  {
    SimpleScene::initRegistries();
  }

  void ClientGame::initEntities()
  {
    SimpleScene::initEntities();
    //  auto enttBackground = m_ecsRegistry->createEntity();
    //  m_entities.push_back(enttBackground);
    //  m_ecsRegistry->addComponent<ComponentRType::Displayable>(
    //    enttBackground,
    //    ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/background_starfield.png"))
  }

  void ClientGame::initEvents()
  {
    SimpleScene::initEvents();

    auto moveSystem = m_ecsRegistry->getSystem<GameEngine::System::Move>();
    m_eventRegistry->subscribe<GameEngine::Event::EventKeyboardInput>(moveSystem);
  }

  void ClientGame::onUpdate(size_t df)
  {
  }
}
