//
// Created by raphael on 12/22/23.
//

#include "scene/SoloHostGame.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "gameEngine/system/EcsSerializer.hpp"
#include "gameEngine/system/TextRenderer.hpp"
#include "gameEngine/system/NetworkEventPusher.hpp"
#include "gameEngine/UI/UIFactory.hpp"
#include "gameEngine/system/InputCatcher.hpp"
#include "gameEngine/event/Events.hpp"
#include "spdlog/spdlog.h"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "sceneController/GraphicController.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/Collider.hpp"
#include "gameEngine/system/Spawning.hpp"
#include "gameEngine/system/Parallax.hpp"
#include "gameEngine/system/Gameplay.hpp"
#include "gameEngine/system/ScriptableEntity.hpp"
#include "script/EnemyLinear.hpp"
#include "script/EnemySinusoidal.hpp"

namespace Rtype::Scene
{
  SoloHostGame::SoloHostGame(Controller::GraphicController &controller)
    : m_controller(controller)
  {
    spdlog::info("SoloHostGame scene created");
  }

  void SoloHostGame::initRegistries()
  {
    auto builder = GameEngine::Builder::RegistryBuilder();

    // Components
    builder.registerAllMandatoryComponent();

    // Systems
    builder.buildSystemAnimation();
    builder.buildSystemInputCatcher();
    builder.buildSystemPhysics();
    builder.buildSystemCollider();
    builder.buildSystemRenderer();
    builder.buildSystemTextRenderer();
    builder.buildSystemControlableEntity();
    builder.buildSystemSpawning();
    builder.buildSystemParallax();
    builder.buildSystemGameplay();
    builder.buildSystemScriptableEntity();
    builder.buildSystemUI();
    m_ecsRegistry = builder.getResult();
  }

  void SoloHostGame::initEntities()
  {
    GameEngine::Scene::SimpleScene::initEntities();

    m_configLoader.loadFromJson("game/rtype/config/game_stage_one.json");
    m_controller.initClassBinding();

    initScripts();
    m_configLoader.loadEntitiesTemplate(getEntityFactory());
    m_configLoader.loadEntities(getEntityFactory());
    m_configLoader.loadStages(getEntityFactory());
  }

  void SoloHostGame::initEvents()
  {
    GameEngine::Scene::SimpleScene::initEvents();

    auto system = m_ecsRegistry->getSystem<GameEngine::System::Spawn>();
    system->setEntityFactory(m_entityFactory);
    getEventRegistry().publish<GameEngine::Event::NewPlayer>(GameEngine::Event::NewPlayer(0));
  }

  void SoloHostGame::initScripts()
  {
    auto &scriptManager = m_entityFactory->getScriptManager();
    scriptManager.registerScript(
      "EnemyLinear",
      std::make_shared<Script::EnemyLinear>(m_ecsRegistry, m_eventRegistry));
    scriptManager.registerScript(
      "EnemySinusoidal",
      std::make_shared<Script::EnemySinusoidal>(m_ecsRegistry, m_eventRegistry));

    m_configLoader.loadScripts(*m_entityFactory);
  }

  void SoloHostGame::onUpdate(size_t df)
  {
    (void)df;
    auto &ecsRegistry = getEcsRegistry();
    try {
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::InputCatcher>();
        system->update(getEventRegistry(), m_controller.getRenderer());
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Parallax>();
        system->update();
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::ScriptableEntity>();
        system->update(getEntityFactory(), df);
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Collider>();
        system->update(getEventRegistry());
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Gameplay>();
        system->update();
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Physics>();
        system->update();
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Spawn>();
        system->update();
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Renderer>();
        system->update(ecsRegistry, m_controller.getRenderer());
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::TextRenderer>();
        system->update(ecsRegistry, m_controller.getRenderer());
      }
    } catch (const std::exception &e) {
      spdlog::error("[Client update] Error: {}", e.what());
    }
  }

} // namespace Server::Game namespace Server::Game
