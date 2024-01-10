//
// Created by raphael on 1/10/24.
//

#include "gameEngine/scene/SceneManager.hpp"

namespace GameEngine::Scene
{
  void SceneManager::initScenes()
  {
    for (auto& scene : m_scenes) {
      scene.second->initRegistries();
      scene.second->initEntities();
      scene.second->initEvents();
    }
  };

  IScene& SceneManager::getCurrent()
  {
    return m_scenes.find(m_currentSceneName);
  }

  void SceneManager::setCurrent(const std::string& name)
  {
    m_currentSceneName = name;
  }

  void SceneManager::addScene(const std::string& name, std::unique_ptr<IScene> scene)
  {
    m_scenes.addScene(name, std::move(scene));
  }
} // namespace GameEngine::Scene
