//
// Created by raphael on 1/10/24.
//

#pragma once
#include "gameEngine/event/EventRegistry.hpp"

namespace GameEngine::Event
{
  class IEventBindable {
   public:
    virtual ~IEventBindable() = default;

    virtual void bindEvent(Event::EventRegistry &eventRegistry) = 0;
  };
} // namespace GameEngine::Event
