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

    IScene &getCurrent();

    void setCurrent(SceneEnum name);

    void addScene(SceneEnum name, std::unique_ptr<IScene> scene);

   private:
    SceneContainer<SceneEnum> m_scenes;
    SceneEnum m_currentSceneName;
  };

}; // namespace GameEngine::Scene
