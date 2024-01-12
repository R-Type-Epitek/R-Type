//
// Created by raphael on 12/21/23.
//

#include "scene/ClientGame.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "gameEngine/system/EcsSerializer.hpp"
#include "gameEngine/system/NetworkEventPusher.hpp"
#include "gameEngine/UI/UIFactory.hpp"
#include "gameEngine/system/InputCatcher.hpp"
#include "gameEngine/event/Events.hpp"
#include "spdlog/spdlog.h"

namespace Rtype::Scene
{

  ClientGame::ClientGame(Controller::GraphicController &controller)
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

    GameEngine::UI::UIFactory uiFactory(m_entities, getEcsRegistry());
    uiFactory.loadUIFromJSON("game/rtype/config/menu_lobby.json");

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

  void ClientGame::initEvents()
  {
    SimpleScene::initEvents();
  }

  void ClientGame::onUpdate(size_t df)
  {
    SimpleScene::onUpdate(df);
    auto &ecsRegistry = getEcsRegistry();
    auto &network = m_controller.getNetwork();

    {
      auto sys_serializer = ecsRegistry.getSystem<GameEngine::System::EcsSerializer>();
      auto ecsState = network.getSerializedEcsState();

      sys_serializer->deserialize(ecsState, getEntityFactory());
    }
    {
      auto system = ecsRegistry.getSystem<GameEngine::System::InputCatcher>();
      system->update(getEventRegistry(), m_controller.getRenderer());
    }
    {
      auto system = ecsRegistry.getSystem<GameEngine::System::NetworkEventPusher>();
      system->update(m_controller.getNetwork());
    }
    {
      auto system = ecsRegistry.getSystem<GameEngine::System::Renderer>();
      system->update(ecsRegistry, m_controller.getRenderer());
    }
  }
} // namespace Rtype::Scene
