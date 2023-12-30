//
// Created by raphael on 12/21/23.
//

#pragma once
#include "IScene.hpp"
#include "SceneContainer.hpp"

namespace GameEngine::Scene
{

  //  TODO: implement with template enum class
  class SceneManager {
   public:
    SceneManager() = default;

    virtual void initScenes() {};
    IScene& getCurrent();
    void setCurrent(std::string name);

   protected:
    SceneContainer m_scenes;

   private:
    std::string m_currentSceneName;
  };

}; // namespace GameEngine::Scene
