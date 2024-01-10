//
// Created by raphael on 1/10/24.
//

#include "gameEngine/scene/SceneManager.hpp"

namespace GameEngine::Scene
{
  SceneContainer::SceneContainer() = default;

  void SceneContainer::addScene(std::string name, std::unique_ptr<IScene> scene)
  {
    auto result = m_scenes.emplace(name, std::move(scene));
    if (!result.second) {
      throw std::invalid_argument("Scene with the same name already exists");
    }
  }

  void SceneContainer::deleteScene(const std::string& name)
  {
    if (!m_scenes.contains(name)) {
      throw std::invalid_argument("Scene with the name doesn't exist");
    }
    m_scenes.erase(name);
  }

  IScene& SceneContainer::getScene(const std::string& name)
  {
    return *m_scenes[name];
  }

  IScene& SceneContainer::find(const std::string& name)
  {
    auto it = m_scenes.find(name);
    if (it != m_scenes.end()) {
      return *(it->second);
    } else {
      std::string msg = "Scene with the specified name not found";
      throw std::out_of_range(msg);
    }
  }

  typename std::map<std::string, std::unique_ptr<IScene>>::iterator SceneContainer::begin()
  {
    return m_scenes.begin();
  }

  typename std::map<std::string, std::unique_ptr<IScene>>::iterator SceneContainer::end()
  {
    return m_scenes.end();
  }

  bool SceneContainer::exist(const std::string& name)
  {
    return m_scenes.contains(name);
  }
} // namespace GameEngine::Scene
