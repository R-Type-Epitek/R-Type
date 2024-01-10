//
// Created by raphael on 12/22/23.
//

#include "scene/HostGame.hpp"
#include "gameEngine/asset/ConfigLoader.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "sceneController/HostGameController.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/Move.hpp"
#include "gameEngine/system/Collider.hpp"

namespace Rtype::Scene
{
  HostGame::HostGame(SceneController::HostGameController& controller)
    : m_controller(controller)
  {
    spdlog::info("HostGame scene created");
  }

  void HostGame::initRegistries()
  {
    auto builder = GameEngine::Builder::RegistryBuilder();

    // Components
    builder.registerAllMandatoryComponent();

    // Systems
    builder.buildSystemPhysics();
    builder.buildSystemEcsSerializer();
    builder.buildSystemInput();
    builder.buildSystemParallax();
    builder.buildSystemMove();
    builder.buildSystemCollider();
    m_ecsRegistry = builder.getResult();
  }

  void HostGame::initEntities()
  {
    m_entityFactory = std::make_shared<GameEngine::Entity::EntityFactory>(m_entities, *m_ecsRegistry);

    ConfigLoader::loadEntities(m_entityFactory);
  }

  void HostGame::initEvents()
  {
    m_eventRegistry = std::make_unique<GameEngine::Event::EventRegistry>();
  }

  void HostGame::onUpdate(size_t df)
  {
    auto& ecsRegistry = getEcsRegistry();
    try {
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Collider>();
        system->update(getEventRegistry());
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Physics>();
        system->update(ecsRegistry);
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Move>();
        system->update(ecsRegistry);
      }
    } catch (const std::exception& e) {
      spdlog::error("[Client update] Error: {}", e.what());
    }
  }

} // namespace Server::Game namespace Server::Game