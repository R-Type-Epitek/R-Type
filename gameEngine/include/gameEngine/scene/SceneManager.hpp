//
// Created by raphael on 12/21/23.
//

#pragma once
#include "IScene.hpp"
#include "ISceneManager.hpp"
#include "SceneContainer.hpp"

namespace GameEngine::Scene
{

  class SceneManager : public ISceneManager {
   public:
    SceneManager() = default;

    void initScenes() final
    {
      for (auto& scene : m_scenes) {
        scene.second->initRegistries();
        scene.second->initEntities();
        scene.second->initEvents();
      }
    };

    IScene& getCurrent() final
    {
      return m_scenes.find(m_currentSceneName);
    }

    void setCurrent(const std::string& name) final
    {
      m_currentSceneName = name;
    }

    void addScene(const std::string& name, std::unique_ptr<IScene> scene) final
    {
      m_scenes.addScene(name, std::move(scene));
    }

   private:
    SceneContainer m_scenes;
    std::string m_currentSceneName;
  };

}; // namespace GameEngine::Scene
