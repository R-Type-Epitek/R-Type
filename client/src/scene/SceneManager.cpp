//
// Created by raphael on 12/21/23.
//

#include "scene/SceneManager.hpp"
#include "scene/GameScene.hpp"
#include <memory>

namespace Client {

void SceneManager::initScenes() {}

void SceneManager::initScenesWithNetwork(Network& network) {
  m_scenes.addScene("GameTest0", std::make_unique<GameScene>(network));
  m_scenes.addScene("GameTest1", std::make_unique<GameScene>(network));
  m_scenes.addScene("GameTest2", std::make_unique<GameScene>(network));
  setCurrent("GameTest0");
}
}  // namespace Client
