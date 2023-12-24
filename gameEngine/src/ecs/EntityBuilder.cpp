//
// Created by raphael on 12/22/23.
//

#include "gameEngine/ecs/EntityBuilder.hpp"
#include "gameEngine/ecs/Registry.hpp"

namespace GameEngine::Builder
{
  EntityBuilder::EntityBuilder(GameEngine::ECS::Registry& registry)
    : m_registry {registry}
  {
  }

  GameEngine::ECS::Entity EntityBuilder::getResult()
  {
    return m_entity;
  }

} // namespace GameEngine::Builder
