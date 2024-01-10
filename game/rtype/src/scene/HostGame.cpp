//
// Created by raphael on 12/22/23.
//

#include "gameEngine/asset/ConfigLoader.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "sceneController/HostGameController.hpp"
#include "scene/HostGame.hpp"

namespace Rtype::Scene
{
  HostGame::HostGame(SceneController::HostGameController &controller)
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
    builder.buildSystemKeyboard();
    builder.buildSystemEcsSerializer();
    builder.buildSystemInput();
    builder.buildSystemParallax();
    builder.buildSystemMove();
    builder.buildSystemCollider();
    m_ecsRegistry = builder.getResult();
  }

  void HostGame::initEntities()
  {
    GameEngine::Scene::SimpleScene::initEntities();

    ConfigLoader::loadEntities(m_entityFactory);
  }

  std::vector<GameEngine::ECS::Entity> HostGame::getEntities()
  {
    return m_entities;
  }

} // namespace Server::Game namespace Server::Game