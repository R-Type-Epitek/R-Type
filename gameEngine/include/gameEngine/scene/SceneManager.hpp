//
// Created by raphael on 12/21/23.
//

#pragma once
#include "IScene.hpp"
#include "SceneContainer.hpp"

namespace GameEngine::Scene
{

  template<typename SceneEnum>
  class SceneManager {
   public:
    SceneManager() = default;

    virtual void initScenes() {};

    IScene &getCurrent()
    {
      return m_scenes.find(m_currentSceneName);
    }

    void setCurrent(SceneEnum name)
    {
      m_currentSceneName = name;
    }

    void addScene(SceneEnum name, std::unique_ptr<IScene> scene)
    {
      m_scenes.addScene(name, std::move(scene));
    }

   private:
    SceneContainer<SceneEnum> m_scenes;
    SceneEnum m_currentSceneName;
  };

}; // namespace GameEngine::Scene
