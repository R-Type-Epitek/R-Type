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
  void SceneManager<SceneEnum>::setCurrent(SceneEnum name)
  {
    m_currentSceneName = name;
  }

  template<typename SceneEnum>
  void SceneManager<SceneEnum>::addScene(SceneEnum name, std::unique_ptr<IScene> scene)
  {
    m_scenes.push(name, std::move(scene));
  }

} // namespace GameEngine::Scene
