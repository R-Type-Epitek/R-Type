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
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/event/Events.hpp"
#include "gameEngine/event/IEventBindable.hpp"
#include "gameEngine/event/EventRegistry.hpp"

namespace GameEngine::System
{

  class ControlableEntity
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder
    , public GameEngine::Event::IEventBindable {
   public:
    void bindEvent(Event::EventRegistry& eventRegistry) final
    {
      eventRegistry.subscribeLambda<Event::MoveUp>(
        ([this](const Event::IEvent& eventRaw) { moveUp(eventRaw); }));
      eventRegistry.subscribeLambda<Event::Movedown>(
        ([this](const Event::IEvent& eventRaw) { moveDown(eventRaw); }));
      eventRegistry.subscribeLambda<Event::MoveLeft>(
        ([this](const Event::IEvent& eventRaw) { moveLeft(eventRaw); }));
      eventRegistry.subscribeLambda<Event::MoveRight>(
        ([this](const Event::IEvent& eventRaw) { moveRight(eventRaw); }));
      eventRegistry.subscribeLambda<Event::PressSpace>(
        ([this](const Event::IEvent& eventRaw) { pressSpace(eventRaw); }));
    }

    void moveUp(const Event::IEvent& eventRaw)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto event = dynamic_cast<const Event::MoveUp&>(eventRaw);
      auto entity = getEntitybyId(event.entity);
      auto& transform = componentManager->getComponent<ComponentRType::Transform>(entity);

      transform.movement = sf::Vector2f(0, -transform.speed);
    }

    void moveDown(const Event::IEvent& eventRaw)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto event = dynamic_cast<const Event::Movedown&>(eventRaw);
      auto entity = getEntitybyId(event.entity);
      auto& transform = componentManager->getComponent<ComponentRType::Transform>(entity);

      transform.movement = sf::Vector2f(0, transform.speed);
    }

    void moveLeft(const Event::IEvent& eventRaw)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto event = dynamic_cast<const Event::MoveLeft&>(eventRaw);
      auto entity = getEntitybyId(event.entity);
      auto& transform = componentManager->getComponent<ComponentRType::Transform>(entity);

      transform.movement = sf::Vector2f(-transform.speed, 0);
    }

    void moveRight(const Event::IEvent& eventRaw)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto event = dynamic_cast<const Event::MoveRight&>(eventRaw);
      auto entity = getEntitybyId(event.entity);

      auto& transform = componentManager->getComponent<ComponentRType::Transform>(entity);

      transform.movement = sf::Vector2f(transform.speed, 0);
    }

    void pressSpace(const Event::IEvent& eventRaw)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto event = dynamic_cast<const Event::PressSpace&>(eventRaw);
      auto entity = getEntitybyId(event.entity);
      auto& position = componentManager->getComponent<ComponentRType::Position>(entity).position;

      Event::PlayerShoot shootEvent("PlayerBullet", event.entity, position.x + 20, position.y);
      getEventRegistry().publish<Event::PlayerShoot>(shootEvent);
    }

   private:
    ECS::Entity getEntitybyId(size_t id)
    {
      return ComponentRType::NetworkedEntity::getEntityByNetworkedId(
        id,
        m_entities,
        *getEcsRegistry().getComponentManager());
    }
  };
} // namespace GameEngine::System
