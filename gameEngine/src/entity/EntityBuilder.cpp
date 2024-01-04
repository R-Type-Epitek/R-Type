//
// Created by raphael on 1/4/24.
//

#include "gameEngine/entity/EntityBuilder.hpp"
#include "gameEngine/ecs/Registry.hpp"

namespace GameEngine::Entity
{
  EntityBuilder::EntityBuilder(GameEngine::ECS::Registry &registry)
    : m_registry {registry}
    , m_entity(newEntity())
  {
  }

  GameEngine::ECS::Entity EntityBuilder::newEntity()
  {
    return m_registry.createEntity();
  }

  GameEngine::ECS::Entity EntityBuilder::getResult()
  {
    return m_entity;
  }

} // GameEngine::Entity
