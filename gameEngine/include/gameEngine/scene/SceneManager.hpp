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
    SceneManager() {};

    void initScenes() final;

    IScene& getCurrent() final;

    void setCurrent(const std::string& name) final;

    void addScene(const std::string& name, std::unique_ptr<IScene> scene) final;

   private:
    SceneContainer m_scenes;
    std::string m_currentSceneName;
  };

}; // namespace GameEngine::Scene
