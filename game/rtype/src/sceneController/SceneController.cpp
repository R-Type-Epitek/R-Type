//
// Created by raphael on 1/10/24.
//

#pragma once
#include "sceneController/SceneController.hpp"

namespace Rtype::Controller
{
  SceneController::SceneController(std::shared_ptr<GameEngine::Scene::ISceneManager> sceneManager)
    : m_sceneManager(std::move(sceneManager)) {};

  GameEngine::Scene::ISceneManager& SceneController::getScene()
  {
    return *m_sceneManager;
  }
} // namespace Rtype::SceneController
