//
// Created by raphael on 1/8/24.
//

#pragma once

#include "gameEngine/event/Events.hpp"
#include "gameEngine/event/IEventListener.hpp"
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <algorithm>

namespace GameEngine::Event
{
  class EventRegistry {
   public:
    template<typename EventType>
    void subscribe(IEventListener& listener)
    {
      char const* typeName = typeid(EventType).name();
      subscribers[typeName].push_back(std::ref(listener));
    }

    template<typename EventType>
    void unsubscribe(IEventListener& listener)
    {
      char const* typeName = typeid(EventType).name();
      auto it = subscribers.find(typeName);
      if (it != subscribers.end()) {
        auto& listeners = it->second;
        listeners.erase(
          std::remove_if(
            listeners.begin(),
            listeners.end(),
            [&listener](const std::reference_wrapper<IEventListener>& storedListener) {
              return &listener == &storedListener.get();
            }),
          listeners.end());
      }
    }

    template<typename EventType>
    void publish(EventType& event)
    {
      char const* typeName = typeid(EventType).name();
      auto it = subscribers.find(typeName);
      if (it != subscribers.end()) {
        for (auto& listener : it->second) {
          event.dispatch(listener);
        }
      }
    }

   private:
    std::unordered_map<char const*, std::vector<std::reference_wrapper<IEventListener>>> subscribers;
  };

} // namespace GameEngine::Event
