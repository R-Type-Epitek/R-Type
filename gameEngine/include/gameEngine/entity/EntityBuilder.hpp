//
// Created by raphael on 1/4/24.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"

namespace GameEngine::Entity
{

  class EntityBuilder {
   public:
    EntityBuilder(GameEngine::ECS::Registry &registry);

    template<typename T>
    void buildComponent(T component)
    {
      m_registry.addComponent(m_entity, component);
    }

    GameEngine::ECS::Entity getResult();

   private:
    GameEngine::ECS::Registry &m_registry;
    GameEngine::ECS::Entity m_entity;

    GameEngine::ECS::Entity newEntity();
  };

} // GameEngine
