//
// Created by raphael on 1/10/24.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/constants/Keybinds.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Hitbox.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/entity/EntityFactory.hpp"
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
      eventRegistry.subscribeLambda<Event::NewPlayer>(
        ([this](const Event::IEvent& eventRaw) { spawnPlayer(eventRaw); }));

      eventRegistry.subscribeLambda<Event::NewEnemy>(
        ([this](const Event::IEvent& eventRaw) { spawnEnemy(eventRaw); }));

      eventRegistry.subscribeLambda<Event::DisconnectedPlayer>(
        ([this](const Event::IEvent& eventRaw) { destroyPlayer(eventRaw); }));

      eventRegistry.subscribeLambda<Event::PlayerShoot>(
        ([this](const Event::IEvent& eventRaw) { spawnEntityType(eventRaw); }));
      eventRegistry.subscribeLambda<Event::DestroyEntity>(
        ([this](const Event::IEvent& eventRaw) { destroyEntity(eventRaw); }));
    }

    void update()
    {
      for (int entityId : m_garbageEntities) {
        getEcsRegistry().destroyEntity(entityId);
      }
      m_garbageEntities.clear();
    }

    void setEntityFactory(std::shared_ptr<Entity::EntityFactory> entityFactory)
    {
      m_entityFactory = std::move(entityFactory);
    }

    void spawnPlayer(const Event::IEvent& eventRaw)
    {
      if (!m_entityFactory) {
        return;
      }
      auto player = dynamic_cast<const Event::NewPlayer&>(eventRaw);

      auto compId = ComponentRType::NetworkedEntity {player.id};
      auto scheme = m_entityFactory->getEntityTemplate("Player");
      m_entityFactory->createFromNetwork(compId, scheme);
    }

    void spawnEnemy(const Event::IEvent&)
    {
    }

    void destroyPlayer(const Event::IEvent& eventRaw)
    {
      if (!m_entityFactory) {
        return;
      }
      auto event = dynamic_cast<const Event::DisconnectedPlayer&>(eventRaw);
      m_garbageEntities.insert(getEntitybyId(event.id));
    }

    void spawnEntityType(const Event::IEvent& eventRaw)
    {
      if (!m_entityFactory) {
        return;
      }
      auto event = dynamic_cast<const Event::PlayerShoot&>(eventRaw);

      auto scheme = m_entityFactory->getEntityTemplate(event.entityTypeName);
      ComponentRType::Position position {event.x, event.y};
      position.isValid = false;
      scheme.position = std::move(position);
      m_entityFactory->createFromTemplateNetwork(scheme);
    }

    void destroyEntity(const Event::IEvent& eventRaw)
    {
      if (!m_entityFactory) {
        return;
      }
      auto event = dynamic_cast<const Event::DestroyEntity&>(eventRaw);
      m_garbageEntities.insert(event.entity);
    }

   private:
    std::set<ECS::Entity> m_garbageEntities {};
    std::shared_ptr<Entity::EntityFactory> m_entityFactory;
    ECS::Entity getEntitybyId(size_t id)
    {
      return ComponentRType::NetworkedEntity::getEntityByNetworkedId(
        id,
        m_entities,
        *getEcsRegistry().getComponentManager());
    }
  };
} // namespace GameEngine::System
