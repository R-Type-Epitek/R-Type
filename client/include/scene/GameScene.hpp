//
// Created by raphael on 12/21/23.
//

#pragma once
#include "EcsGameController.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/scene/IScene.hpp"

namespace Client {
class GameScene : public GameEngine::Scene::IScene {
 public:
  GameScene();
  void update() final;
  GameEngine::ECS::Registry& getECS() final;

 private:
  ECS::EcsGameController m_ecsController;
  //  GameEngine::ECS::Registry m_registry;
};
}  // namespace Client
