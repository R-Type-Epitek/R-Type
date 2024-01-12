//
// Created by raphael on 1/10/24.
//

#pragma once
#include "gameEngine/scene/ISceneManager.hpp"

namespace Rtype::Controller
{
  class SceneController {
   public:
    explicit SceneController(std::shared_ptr<GameEngine::Scene::ISceneManager> sceneManager);
    ~SceneController() = default;

    GameEngine::Scene::ISceneManager& getScenes();

   private:
    std::shared_ptr<GameEngine::Scene::ISceneManager> m_sceneManager;
  };
} // namespace Rtype::SceneController
