//
// Created by raphael on 12/21/23.
//

#include "scene/SceneManager.hpp"

#include "scene/WelcomeScene.hpp"
#include "scene/LobbyScene.hpp"
#include "scene/GameScene.hpp"

#include <memory>

namespace Client::Scene
{
  void SceneManager::initScenes()
  {
  }

  void SceneManager::initScenesWithNetwork(Network& network)
  {
    addScene(SceneType::Lobby, std::make_unique<LobbyScene>(network));
    addScene(SceneType::Game, std::make_unique<GameScene>(network));
    addScene(SceneType::Welcome, std::make_unique<WelcomeScene>(network));
    setCurrent(SceneType::Game);
  }
} // namespace Client
