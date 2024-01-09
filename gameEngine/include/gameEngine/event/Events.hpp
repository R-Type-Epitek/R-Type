//
// Created by raphael on 1/8/24.
//

#pragma once
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/event/IEvent.hpp"

namespace GameEngine::Event
{

  class EventCollision : public IEvent {
   public:
    EventCollision(const ECS::Entity &entityA, const ECS::Entity &entityB)
      : entityA {entityA}
      , m_entityB {entityB} {};

   private:
    ECS::Entity entityA;
    ECS::Entity m_entityB;
  };
} // namespace GameEngine::Event
