//
// Created by raphael on 1/10/24.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/constants/Keybinds.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/event/Events.hpp"
#include "gameEngine/event/IEventBindable.hpp"
#include "gameEngine/event/EventRegistry.hpp"

namespace GameEngine::System
{

  class Spawn
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder
    , public GameEngine::Event::IEventBindable {
   public:
    void bindEvent(Event::EventRegistry& eventRegistry) final
    {
      eventRegistry.subscribeLambda<Event::NewPlayer>(([this](const Event::IEvent& eventRaw) {
        spawnPlayer(eventRaw);
      }));

      eventRegistry.subscribeLambda<Event::NewEnemy>(([this](const Event::IEvent& eventRaw) {
        spawnEnemy(eventRaw);
      }));

      eventRegistry.subscribeLambda<Event::DisconnectedPlayer>(([this](const Event::IEvent& eventRaw) {
        destroyPlayer(eventRaw);
      }));
    }

    void spawnPlayer(const Event::IEvent&)
    {
    }

    void spawnEnemy(const Event::IEvent&)
    {
    }

    void destroyPlayer(const Event::IEvent&)
    {
    }
  };
} // namespace GameEngine::System
