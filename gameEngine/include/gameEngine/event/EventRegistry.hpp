//
// Created by raphael on 1/8/24.
//

#pragma once

#include "gameEngine/event/Events.hpp"
#include "gameEngine/event/IEventListener.hpp"
#include "gameEngine/event/EventListenerWrapper.hpp"
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <algorithm>
#include <functional>

namespace GameEngine::Event
{
  class EventRegistry {
   public:
    template<typename EventType>
    void subscribe(std::shared_ptr<IEventListener> listener)
    {
      char const* typeName = typeid(EventType).name();
      subscribers[typeName].push_back(listener);
    }

    template<typename EventType>
    void subscribeLambda(std::function<void(const IEvent& event)> lambdaListener)
    {
      char const* typeName = typeid(EventType).name();
      auto listener = std::make_shared<EventListenerWrapper>(lambdaListener);
      subscribers[typeName].push_back(listener);
    }

    template<typename EventType>
    void unsubscribe(std::shared_ptr<IEventListener> listener)
    {
      char const* typeName = typeid(EventType).name();
      auto it = subscribers.find(typeName);
      if (it != subscribers.end()) {
        auto& listeners = it->second;
        listeners.erase(
          std::remove_if(
            listeners.begin(),
            listeners.end(),
            [&listener](const std::shared_ptr<IEventListener>& storedListener) {
              return listener.get() == storedListener.get();
            }),
          listeners.end());
      }
    }

    template<typename EventType>
    void publish(const IEvent& event)
    {
      char const* typeName = typeid(EventType).name();
      auto it = subscribers.find(typeName);
      if (it != subscribers.end()) {
        for (auto& listener : it->second) {
          listener->handleEvent(event);
        }
      }
    }

   private:
    using ListenerList = std::vector<std::shared_ptr<IEventListener>>;
    std::unordered_map<char const*, ListenerList> subscribers;
  };

} // namespace GameEngine::Event
