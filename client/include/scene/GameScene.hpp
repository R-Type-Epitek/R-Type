//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/scene/IScene.hpp"
#include <memory>
#include <vector>

namespace Client {
class GameScene : public GameEngine::Scene::IScene {
 public:
  GameScene();
  void update() final;

  void initRegistry() final;

  void initEntities() final;

  GameEngine::ECS::Registry& getECS() final;

 private:
  std::vector<GameEngine::ECS::Entity> m_entities;
  std::unique_ptr<GameEngine::ECS::Registry> m_registry;
};
}  // namespace Client
