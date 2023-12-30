//
// Created by raphael on 12/21/23.
//

#include "gameEngine/scene/SceneManager.hpp"

#include <cassert>
#include <string>
#include <utility>

namespace GameEngine::Scene
{

  IScene& SceneManager::getCurrent()
  {
    return m_scenes.find(m_currentSceneName);
  }

  void SceneManager::setCurrent(std::string name)
  {
    m_currentSceneName = std::move(name);
  }

} // namespace GameEngine::Scene
