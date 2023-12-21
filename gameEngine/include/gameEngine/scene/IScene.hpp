//
// Created by raphael on 12/20/23.
//

#pragma once

namespace GameEngine::Scene {
class IScene {
 public:
  virtual ~IScene() = default;

  virtual void render() = 0;
};
}  // namespace GameEngine::Scene
