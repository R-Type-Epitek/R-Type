//
// Created by raphael on 1/4/24.
//

#pragma once
#include "gameEngine/UI/Window.hpp"
#include "gameEngine/constants/Keybinds.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "IUpdateSystem.hpp"

namespace GameEngine::System
{

  class Input : public GameEngine::ECS::System {
   public:
    void update(GameEngine::ECS::Registry& registry, size_t playerId, GameEngine::Keybinds eventKey)
    {
      auto& componentManager = registry.getComponentManager();

      for (auto const& entity : m_entities) {
        auto& compId = componentManager->getComponent<ComponentRType::NetworkedEntity>(entity);
        if (compId.id == playerId) {
          dispatchEvent(*componentManager, entity, eventKey);
        }
      }
    };

   private:
    static void dispatchEvent(
      GameEngine::ECS::ComponentManager& componentManager,
      const GameEngine::ECS::Entity& entity,
      GameEngine::Keybinds eventKey)
    {
      auto& transform = componentManager.getComponent<ComponentRType::Transform>(entity);
      const float speed = transform.speed;

      switch (eventKey) {
        case GameEngine::Keybinds::Up:
          transform.movement = sf::Vector2f(0, -speed);
          break;
        case GameEngine::Keybinds::Down:
          transform.movement = sf::Vector2f(0, speed);
          break;
        case GameEngine::Keybinds::Left:
          transform.movement = sf::Vector2f(-speed, 0);
          break;
        case GameEngine::Keybinds::Right:
          transform.movement = sf::Vector2f(speed, 0);
          break;
        case GameEngine::Keybinds::Space:
          pressSpace(componentManager, entity);
          transform.movement = sf::Vector2f(0, 0);
          break;
        default:
          break;
      }
    }

    static void pressSpace(GameEngine::ECS::ComponentManager&, const GameEngine::ECS::Entity&) {};
  };
} // namespace GameEngine::System
