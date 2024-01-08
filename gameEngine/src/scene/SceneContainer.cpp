#include "gameEngine/scene/SceneContainer.hpp"

#include <stdexcept>

namespace GameEngine::Scene
{
  template<typename SceneEnum>
  void SceneContainer<SceneEnum>::addScene(SceneEnum name, std::unique_ptr<IScene> scene)
  {
    auto result = m_scenes.emplace(name, std::move(scene));
    if (!result.second) {
      throw std::invalid_argument("Scene with the same name already exists");
    }
  }

  template<typename SceneEnum>
  void SceneContainer<SceneEnum>::deleteScene(SceneEnum name)
  {
    if (!exist(name)) {
      throw std::invalid_argument("Scene with the specified name doesn't exist");
    }
    m_scenes.erase(name);
  }

  template<typename SceneEnum>
  IScene& SceneContainer<SceneEnum>::getScene(SceneEnum name)
  {
    return *m_scenes[name];
  }

  template<typename SceneEnum>
  bool SceneContainer<SceneEnum>::exist(SceneEnum name)
  {
    return m_scenes.contains(name);
  }

  template<typename SceneEnum>
  IScene& SceneContainer<SceneEnum>::find(SceneEnum name)
  {
    auto it = m_scenes.find(name);
    if (it != m_scenes.end()) {
      return *(it->second);
    } else {
      std::string msg = "Scene with the specified name not found";
      throw std::out_of_range(msg);
    }
  }
} // namespace GameEngine::Scene
