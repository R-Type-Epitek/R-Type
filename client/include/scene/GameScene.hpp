//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/scene/IScene.hpp"

namespace Client {
class GameScene : public GameEngine::Scene::IScene {
 public:
  GameScene();
  void update() final;
  Registry& getECS() final;

 private:
  Registry m_registry;
};
}  // namespace Client