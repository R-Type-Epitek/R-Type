//
// Created by raphael on 1/9/24.
//

#pragma once

//
// Created by raphael on 1/8/24.
//

#pragma once
#include "gameEngine/event/IEvent.hpp"
#include "gameEngine/event/IEventListener.hpp"

#include <functional>
#include <utility>

namespace GameEngine::Event
{

  class EventListenerWrapper : public IEventListener {
   public:
    explicit EventListenerWrapper(std::function<void(const IEvent &event)> callback)
      : m_callback {std::move(callback)}
    {
    }

    void handleEvent(const IEvent &event) final
    {
      m_callback(event);
    };

   private:
    std::function<void(const IEvent &event)> m_callback;
  };
} // namespace GameEngine::Event
