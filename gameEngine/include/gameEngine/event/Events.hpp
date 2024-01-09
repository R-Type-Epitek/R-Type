//
// Created by raphael on 1/8/24.
//

#pragma once
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/event/IEvent.hpp"
#include "gameEngine/constants/Keybinds.hpp"

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

  class EventKeyboardInput : public IEvent {
   public:
    explicit EventKeyboardInput(const Keybinds &key)
      : m_key {key}
    {
    }

    const Keybinds &getKey() const
    {
      return m_key;
    }

   private:
    Keybinds m_key;
  };

} // namespace GameEngine::Event
