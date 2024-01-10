//
// Created by raphael on 1/10/24.
//

#pragma once
#include "IScene.hpp"
#include "SceneContainer.hpp"

namespace GameEngine::Scene
{
  class ISceneManager {
   public:
    virtual ~ISceneManager() = default;

    virtual void initScenes() = 0;

    virtual IScene& getCurrent() = 0;

    virtual void setCurrent(const std::string& name) = 0;

    virtual void addScene(const std::string& name, std::unique_ptr<IScene> scene) = 0;
  };

} // namespace GameEngine::Scene
