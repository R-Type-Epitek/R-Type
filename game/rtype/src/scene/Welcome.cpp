//
// Created by raphael on 12/21/23.
//

#include "scene/Welcome.hpp"
#include "gameEngine/system/InputCatcher.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/UiElement.hpp"
#include "gameEngine/UI/UIFactory.hpp"
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
    GameEngine::UI::UIFactory uiFactory(m_entities, getEcsRegistry());
    uiFactory.loadUIFromJSON("game/rtype/config/menu_welcome.json");

    m_controller.initClassBinding();
    auto &componentManager = getEcsRegistry().getComponentManager();
    auto configElements = uiFactory.getUIElements();
    for (auto &[configId, entity] : configElements) {
      if (componentManager->hasComponent<ComponentRType::Clickable>(entity)) {
        auto &uiElement = componentManager->getComponent<ComponentRType::UIElement>(entity);
        auto &clickable = componentManager->getComponent<ComponentRType::Clickable>(entity);
        clickable.callback = m_controller.getBinding(uiElement.callBackValue);
      }
    }
  }

  void Welcome::initEvents()
  {
    SimpleScene::initEvents();
  }

  void Welcome::onUpdate(size_t df)
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
} // namespace Rtype::Scene
