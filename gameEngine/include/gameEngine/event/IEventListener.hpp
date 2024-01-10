//
// Created by raphael on 1/8/24.
//

#pragma once
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/event/Events.hpp"

namespace GameEngine::Event
{
  class IEventListener {
   public:
    virtual ~IEventListener() = default;

    virtual void handleEvent(const IEvent &event) = 0;
  };
} // namespace GameEngine::Event
