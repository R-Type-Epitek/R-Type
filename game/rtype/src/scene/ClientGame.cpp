//
// Created by raphael on 12/21/23.
//

#include "scene/ClientGame.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "gameEngine/system/EcsSerializer.hpp"
#include "gameEngine/system/NetworkEventPusher.hpp"
#include "gameEngine/system/InputCatcher.hpp"
#include "gameEngine/event/Events.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
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
    auto enttBackground = m_ecsRegistry->createEntity();
    m_entities.push_back(enttBackground);
    m_ecsRegistry->addComponent<ComponentRType::Displayable>(
      enttBackground,
      ComponentRType::Displayable(
        GameEngine::Asset::getTexture("game/rtype/assets/background_starfield.png")));
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
