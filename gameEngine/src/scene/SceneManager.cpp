//
// Created by raphael on 12/21/23.
//

#include "gameEngine/scene/SceneManager.hpp"

#include <cassert>
#include <string>
#include <utility>

namespace GameEngine::Scene
{

  template<typename SceneEnum>
  IScene &SceneManager<SceneEnum>::getCurrent()
  {
    return m_scenes.find(m_currentSceneName);
  }

  template<typename SceneEnum>
  void SceneManager<SceneEnum>::setCurrent(SceneEnum &name)
  {
    m_currentSceneName = name;
  }

} // namespace GameEngine::Scene
