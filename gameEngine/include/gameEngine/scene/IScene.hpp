//
// Created by raphael on 12/20/23.
//

#pragma once
#include "gameEngine/ecs/"

namespace GameEngine::Scene {
class IScene {
 public:
  virtual ~IScene() = default;

  virtual void update() = 0;
  virtual void getECS() = 0;
  // TODO  ADD ecs Method
};
}  // namespace GameEngine::Scene
