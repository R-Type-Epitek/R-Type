//
// Created by raphael on 1/12/24.
//

#pragma once

//
// Created by Alexandre Decobert on 16/12/2023.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/event/IEventBindable.hpp"
#include "gameEngine/event/Events.hpp"
#include "gameEngine/event/IEvent.hpp"

namespace GameEngine::System
{

  class UI
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder
    , public Event::IEventBindable {
   public:
    void bindEvent(Event::EventRegistry& eventRegistry) final
    {
      eventRegistry.subscribeLambda<Event::MouseButtonPressed>(
        ([this](const Event::IEvent& eventRaw) { handleClick(eventRaw); }));
    }

    void update()
    {
      for (auto const& entity : m_entities) {
        auto& componentManager = getEcsRegistry().getComponentManager();
        auto& displayable = componentManager->getComponent<ComponentRType::Displayable>(entity);
        auto& position = componentManager->getComponent<ComponentRType::Position>(entity);

        displayable.sprite.setPosition(position.position);
      }
    }

    void handleClick(const Event::IEvent& eventRaw)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto event = dynamic_cast<const Event::MouseButtonPressed&>(eventRaw);

      for (auto const& entity : m_entities) {
        auto& clickable = componentManager->getComponent<ComponentRType::Clickable>(entity);
        auto& displayable = componentManager->getComponent<ComponentRType::Displayable>(entity);
        auto& position = componentManager->getComponent<ComponentRType::Position>(entity);

        if (
          displayable.sprite.getGlobalBounds().contains(
            static_cast<float>(event.x),
            static_cast<float>(event.y)) &&
          clickable.callback) {
          clickable.callback();
        }
        displayable.sprite.setPosition(position.position);
      }
    }
  };
} // namespace GameEngine::System
