//
// Created by raphael on 1/4/24.
//

#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/asset/AssetManager.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/Controllable.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Displayable.hpp"

namespace GameEngine::Entity
{

  EntityFactory::EntityFactory(std::vector<GameEngine::ECS::Entity> &entities, ECS::Registry &registry)
    : m_entities(entities)
    , m_registry(registry)
  {
  }

  GameEngine::ECS::Entity EntityFactory::create(const BulletPayload &payload)
  {
    spdlog::info("[EntityFactory] Creating Bullet entity...");
    return createBullet(payload);
  }
  GameEngine::ECS::Entity EntityFactory::create(const EnemyPayload &payload)

  {
    spdlog::info("[EntityFactory] Creating Enemy entity...");
    return createEnemy(payload);
  };

  GameEngine::ECS::Entity EntityFactory::create(const PlayerPayload &payload)
  {
    spdlog::info("[EntityFactory] Creating Player entity...");
    return createPlayer(payload);
  };

  GameEngine::ECS::Entity EntityFactory::createPlayer(PlayerPayload payload)
  {
    auto entity = newEntity();
    m_registry.addComponent(entity, ComponentRType::MetaData {});
    m_registry.addComponent(entity, ComponentRType::NetworkedEntity {});
    m_registry.addComponent(entity, ComponentRType::Controllable {});
    m_registry.addComponent(entity, ComponentRType::Position {});
    m_registry.addComponent(entity, ComponentRType::Transform {});

    if (!payload.light) {
      m_registry.addComponent(
        entity,
        ComponentRType::Displayable(GameEngine::Asset::getTexture(payload.texturePath)));
    }
    return entity;
  }

  GameEngine::ECS::Entity EntityFactory::createEnemy(EnemyPayload payload)
  {
    auto entity = newEntity();
    m_registry.addComponent(entity, ComponentRType::MetaData {});
    m_registry.addComponent(entity, ComponentRType::NetworkedEntity {});
    m_registry.addComponent(entity, ComponentRType::Controllable {});
    m_registry.addComponent(entity, ComponentRType::Position {});
    m_registry.addComponent(entity, ComponentRType::Transform {});

    if (!payload.light) {
      m_registry.addComponent(
        entity,
        ComponentRType::Displayable(GameEngine::Asset::getTexture(payload.texturePath)));
    }
    return entity;
  }

  GameEngine::ECS::Entity EntityFactory::createBullet(BulletPayload payload)
  {
    auto entity = newEntity();
    m_registry.addComponent(entity, ComponentRType::MetaData {});
    m_registry.addComponent(entity, ComponentRType::NetworkedEntity {});
    m_registry.addComponent(entity, ComponentRType::Position {});
    m_registry.addComponent(entity, ComponentRType::Transform {});

    if (!payload.light) {
      m_registry.addComponent(
        entity,
        ComponentRType::Displayable(GameEngine::Asset::getTexture(payload.texturePath)));
    }
    return entity;
  }

  GameEngine::ECS::Entity EntityFactory::newEntity()
  {
    auto entity = m_registry.createEntity();
    m_entities.push_back(entity);
    return entity;
  }

} // GameEngine::Entity