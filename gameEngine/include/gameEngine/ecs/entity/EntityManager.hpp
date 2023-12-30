//
// Created by raphael on 11/28/23.
//

#pragma once

#include "Entity.hpp"
#include "gameEngine/ecs/Signature.hpp"

#include <array>
#include <cstdint>
#include <queue>

namespace GameEngine::ECS
{
  class EntityManager {
   public:
    EntityManager();

    Entity createEntity();

    void destroyEntity(Entity entity);

    void setSignature(Entity entity, Signature signature);

    Signature getSignature(Entity entity);

   private:
    std::queue<Entity> m_availableEntities {};

    std::array<Signature, ECS::MAX_ENTITIES> m_signatures {};

    uint32_t m_livingEntityCount {};
  };
} // namespace GameEngine::ECS
