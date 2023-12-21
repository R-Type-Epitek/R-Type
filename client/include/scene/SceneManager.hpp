//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/scene/SceneManager.hpp"

namespace Client {
class SceneManager : GameEngine::Scene::SceneManager {
 public:
  void initScenes() final;
};

}  // namespace Client
