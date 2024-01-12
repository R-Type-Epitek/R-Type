//
// Created by raphael on 12/21/23.
//

#include "scene/Lobby.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "gameEngine/system/InputCatcher.hpp"
#include "gameEngine/UI/UIFactory.hpp"
#include "gameEngine/event/Events.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/Text.hpp"
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
    GameEngine::UI::UIFactory uiFactory(m_entities, getEcsRegistry());
    uiFactory.loadUIFromJSON("game/rtype/config/menu_lobby.json");
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
