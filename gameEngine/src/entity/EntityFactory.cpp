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
#include "gameEngine/entity/EntityBuilder.hpp"

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

  void EntityFactory::createFromMetaData(ComponentRType::MetaData &data)
  {
    spdlog::info("[EntityFactory] Creating entity from Metadata...");
  }

  GameEngine::ECS::Entity EntityFactory::createPlayer(PlayerPayload payload)
  {
    auto builder = EntityBuilder(m_registry);
    builder.buildComponent(ComponentRType::MetaData {});
    builder.buildComponent(ComponentRType::NetworkedEntity {});
    builder.buildComponent(ComponentRType::Controllable {});
    builder.buildComponent(ComponentRType::Position {});
    builder.buildComponent(ComponentRType::Transform {});
    if (!payload.light) {
      builder.buildComponent(ComponentRType::Displayable(GameEngine::Asset::getTexture(payload.texturePath)));
    }

    auto entity = builder.getResult();
    m_entities.push_back(entity);
    return entity;
  }

  GameEngine::ECS::Entity EntityFactory::createEnemy(EnemyPayload payload)
  {
    auto builder = EntityBuilder(m_registry);
    builder.buildComponent(ComponentRType::MetaData {});
    builder.buildComponent(ComponentRType::NetworkedEntity {});
    builder.buildComponent(ComponentRType::Controllable {});
    builder.buildComponent(ComponentRType::Position {});
    builder.buildComponent(ComponentRType::Transform {});
    if (!payload.light) {
      builder.buildComponent(ComponentRType::Displayable(GameEngine::Asset::getTexture(payload.texturePath)));
    }

    auto entity = builder.getResult();
    m_entities.push_back(entity);
    return entity;
  }

  GameEngine::ECS::Entity EntityFactory::createBullet(BulletPayload payload)
  {
    auto builder = EntityBuilder(m_registry);
    builder.buildComponent(ComponentRType::MetaData {});
    builder.buildComponent(ComponentRType::NetworkedEntity {});
    builder.buildComponent(ComponentRType::Position {});
    builder.buildComponent(ComponentRType::Transform {});
    if (!payload.light) {
      builder.buildComponent(ComponentRType::Displayable(GameEngine::Asset::getTexture(payload.texturePath)));
    }
    
    auto entity = builder.getResult();
    m_entities.push_back(entity);
    return entity;
  }

} // GameEngine::Entity