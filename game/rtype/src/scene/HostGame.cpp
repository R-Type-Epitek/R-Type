//
// Created by raphael on 12/22/23.
//

#include "scene/HostGame.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "sceneController/HostGameController.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/Collider.hpp"
#include "gameEngine/system/Spawning.hpp"
#include "gameEngine/system/Parallax.hpp"

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
    builder.buildSystemCollider();
    builder.buildSystemEcsSerializer();
    builder.buildSystemControlableEntity();
    builder.buildSystemPhysics();
    builder.buildSystemSpawning();
    builder.buildSystemParallax();
    m_ecsRegistry = builder.getResult();
  }

  void HostGame::initEntities()
  {
    GameEngine::Scene::SimpleScene::initEntities();

    m_configLoader.loadFromJson("game/rtype/config/game_stage_one.json");
    m_configLoader.loadEntitiesTemplate(getEntityFactory());
    m_configLoader.loadEntities(getEntityFactory());
  }

  void HostGame::initEvents()
  {
    GameEngine::Scene::SimpleScene::initEvents();

    auto system = m_ecsRegistry->getSystem<GameEngine::System::Spawn>();
    system->setEntityFactory(m_entityFactory);
  }

  void HostGame::onUpdate(size_t df)
  {
    (void)df;
    auto& ecsRegistry = getEcsRegistry();
    try {
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Parallax>();
        system->update();
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Collider>();
        system->update(getEventRegistry());
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Physics>();
        system->update();
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Spawn>();
        system->update();
      }
    } catch (const std::exception& e) {
      spdlog::error("[Client update] Error: {}", e.what());
    }
  }

} // namespace Server::Game namespace Server::Game