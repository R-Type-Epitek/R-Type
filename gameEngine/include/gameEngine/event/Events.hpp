//
// Created by raphael on 1/8/24.
//

#pragma once
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/event/IEvent.hpp"
#include "gameEngine/constants/Keybinds.hpp"

namespace GameEngine::Event
{
  struct EventCollision : public IEvent {
    explicit EventCollision(const ECS::Entity &entityA, const ECS::Entity &entityB)
      : entityA {entityA}
      , entityB {entityB} {};

    const ECS::Entity &entityA;
    const ECS::Entity &entityB;
  };

  struct EventKeyboardInput : public IEvent {
    explicit EventKeyboardInput(const Keybinds &key)
      : key {key}
    {
    }

    Keybinds key;
  };

} // namespace GameEngine::Event
