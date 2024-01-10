//
// Created by raphael on 1/10/24.
//
#include "game/Game.hpp"
#include "sceneController/HostGameController.hpp"
#include "scene/HostGame.hpp"
#include "gameEngine/system/EcsSerializer.hpp"
#include <memory>

namespace Server::Game
{

  void Game::load()
  {
    spdlog::info("Starting Game Engine...");
    m_coreGE = std::make_unique<GameEngine::Core::Core>("Rtype server");
    m_coreGE->loadPlugins();
    m_coreGE->disableGUI();
    m_coreGE->setTicksPerSecond(200);

    initScenes();
    spdlog::info("Done");
  }

  void Game::initScenes()
  {
    auto controller = Rtype::SceneController::HostGameController();
    m_coreGE->addScene("hostGame", std::make_unique<Rtype::Scene::HostGame>(controller));

    m_coreGE->setCurrentScene("hostGame");
    m_coreGE->loadScenes();
  }

  std::vector<std::vector<char>> Game::getSerializedEntities()
  {
    auto& registry = m_coreGE->getCurrentScene().getEcsRegistry();

    auto system = registry.getSystem<GameEngine::System::EcsSerializer>();
    return system->serialise(registry);
  }

  void Game::update(unsigned int df)
  {
  }

  void Game::pushEvent(Event event, Player player)
  {
  }

} // namespace Server
