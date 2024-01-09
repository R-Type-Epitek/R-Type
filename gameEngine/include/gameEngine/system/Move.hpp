//
// Created by raphael on 1/4/24.
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
#include "gameEngine/event/IEventListener.hpp"

namespace GameEngine::System
{

  class Move
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder
    , public Event::IEventListener {
   public:
    void update(GameEngine::ECS::Registry& registry)
    {
      auto& componentManager = registry.getComponentManager();

      for (auto const& entity : m_entities) {
        auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
        auto& transform = componentManager->getComponent<ComponentRType::Transform>(entity);
        auto& position = componentManager->getComponent<ComponentRType::Position>(entity);

        position.position += transform.movement;
        spriteC.sprite.move(transform.movement);
        position.position = spriteC.sprite.getPosition();
        position.latestPosition = position.position;
      }
    }

    void updateClient(GameEngine::ECS::Registry& registry)
    {
      auto& componentManager = registry.getComponentManager();

      for (auto const& entity : m_entities) {
        auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
        auto& transform = componentManager->getComponent<ComponentRType::Transform>(entity);
        auto& position = componentManager->getComponent<ComponentRType::Position>(entity);

        if (registry.hasComponent<ComponentRType::Clickable>(entity)) {
          spriteC.sprite.setPosition(position.position);
        }
        spriteC.sprite.move(transform.movement);
      }
    }

    void handleEvent(const Event::IEvent& eventRaw) final
    {
      Event::EventKeyboardInput event = dynamic_cast<const Event::EventKeyboardInput&>(eventRaw);
      switch (event.getKey()) {
        case Keybinds::Up:
          moveUp();
          break;
        case Keybinds::Down:
          moveDown();
          break;
        case Keybinds::Left:
          moveLeft();
          break;
        case Keybinds::Right:
          moveRight();
          break;
        default:
          break;
      }
    }

    void moveUp()
    {
      spdlog::info("Move up");
    }

    void moveDown()
    {
      spdlog::info("Move down");
    }

    void moveLeft()
    {
      spdlog::info("Move left");
    }

    void moveRight()
    {
      spdlog::info("Move right");
    }
  };
} // namespace GameEngine::System
