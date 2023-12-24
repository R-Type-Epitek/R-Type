//
// Created by raphael on 12/22/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include <vector>

namespace GameEngine::Builder {

class EntityBuilder {
 public:
  EntityBuilder(GameEngine::ECS::Registry& registry);
  GameEngine::ECS::Entity getResult();

 private:
  GameEngine::ECS::Entity m_entity;
  GameEngine::ECS::Registry& m_registry;
};

}  // namespace GameEngine::Builder
