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
      GameEngine::ECS::ComponentManager componentManager,
      const GameEngine::ECS::Entity& entity,
      GameEngine::Keybinds eventKey)
    {
      const float offset = 0.5;
      switch (eventKey) {
        case GameEngine::Keybinds::Up:
          moveOffset(componentManager, entity, sf::Vector2f(0, -offset));
          break;
        case GameEngine::Keybinds::Down:
          moveOffset(componentManager, entity, sf::Vector2f(0, offset));
          break;
        case GameEngine::Keybinds::Left:
          moveOffset(componentManager, entity, sf::Vector2f(-offset, 0));
          break;
        case GameEngine::Keybinds::Right:
          moveOffset(componentManager, entity, sf::Vector2f(offset, 0));
          break;
        case GameEngine::Keybinds::Space:
          pressSpace(componentManager, entity);
          break;
        default:
          moveOffset(componentManager, entity, sf::Vector2f(0, 0));
          break;
      }
    }

    static void moveOffset(
      GameEngine::ECS::ComponentManager& componentManager,
      const GameEngine::ECS::Entity& entity,
      sf::Vector2f offset)
    {
      auto& comp = componentManager.getComponent<ComponentRType::Position>(entity);
      comp.position = offset;
    }

    static void pressSpace(GameEngine::ECS::ComponentManager&, const GameEngine::ECS::Entity&) {};
  };
} // namespace GameEngine::System
