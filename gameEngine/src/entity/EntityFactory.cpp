//
// Created by raphael on 1/4/24.
//

#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/asset/AssetManager.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/Controllable.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Hitbox.hpp"
#include "gameEngine/entity/EntityBuilder.hpp"

namespace GameEngine::Entity
{

  EntityBluePrint EntityFactory::playerEntity {
    .light = false,
    .blueprint = {
      .transform = true,
      .displayable = true,
      .controllable = true,
      .networkedEntity = true,
      .metaData = true,
      .position = true,
      .gravity = true,
      .hitbox = true,
    }};

  EntityBluePrint EntityFactory::enemyEntity {
    .light = false,
    .blueprint = {
      .transform = true,
      .displayable = true,
      .controllable = true,
      .networkedEntity = true,
      .metaData = true,
      .position = true,
      .gravity = true,
      .hitbox = true,
    }};

  EntityBluePrint EntityFactory::bulletEntity {
    .light = false,
    .blueprint = {
      .transform = true,
      .displayable = true,
      .controllable = true,
      .networkedEntity = true,
      .metaData = true,
      .position = true,
      .gravity = true,
      .hitbox = true,
    }};

  EntityFactory::EntityFactory(std::vector<GameEngine::ECS::Entity> &entities, ECS::Registry &registry)
    : m_entities(entities)
    , m_registry(registry)
  {
  }

  GameEngine::ECS::Entity EntityFactory::create(const EntityType &type)
  {
    spdlog::info("[EntityFactory] Creating entity...");
    switch (type) {
      case EntityType::Player:
        spdlog::info("[EntityFactory] Creating Player entity...");
        return createFromBluePrint(playerEntity);
      case EntityType::Enemy:
        spdlog::info("[EntityFactory] Creating Enemy entity...");
        return createFromBluePrint(enemyEntity);
      case EntityType::Bullet:
        spdlog::info("[EntityFactory] Creating Bullet entity...");
        return createFromBluePrint(bulletEntity);
      case EntityType::None:
        throw std::runtime_error("Cannot create entity of type None");
      default:
        throw std::runtime_error("Unknown entity type");
    }
  }

  GameEngine::ECS::Entity EntityFactory::createFromNetwork(
    ComponentRType::NetworkedEntity &id,
    ComponentRType::MetaData &metaData)
  {
    spdlog::info("[EntityFactory] Creating entity from Network...");
    auto entity = create(metaData.entityType);
    auto &componentManager = m_registry.getComponentManager();

    auto &idMem = componentManager->getComponent<ComponentRType::NetworkedEntity>(entity);
    auto &metaDataMem = componentManager->getComponent<ComponentRType::MetaData>(entity);
    idMem = id;
    metaDataMem = metaData;

    auto compDisplay = ComponentRType::Displayable(GameEngine::Asset::getTexture(metaData.texturePath));
    auto &compDisplayMem = componentManager->getComponent<ComponentRType::Displayable>(entity);
    compDisplayMem = compDisplay;

    return entity;
  }

  GameEngine::ECS::Entity EntityFactory::createFromBluePrint(EntityBluePrint const &payload)
  {
    spdlog::info("[EntityFactory] Creating entity from BluePrint...");

    auto builder = EntityBuilder(m_registry);
    if (payload.blueprint.transform) {
      builder.buildComponent(ComponentRType::Transform {});
    }
    if (payload.blueprint.displayable) {
      builder.buildComponent(ComponentRType::Displayable(GameEngine::Asset::getTexture()));
    }
    if (payload.blueprint.clickable) {
      builder.buildComponent(ComponentRType::Clickable {});
    }
    if (payload.blueprint.controllable) {
      builder.buildComponent(ComponentRType::Controllable {});
    }
    if (payload.blueprint.networkedEntity) {
      builder.buildComponent(ComponentRType::NetworkedEntity {});
    }
    if (payload.blueprint.metaData) {
      builder.buildComponent(ComponentRType::MetaData {});
    }
    if (payload.blueprint.position) {
      builder.buildComponent(ComponentRType::Position {});
    }
    if (payload.blueprint.gravity) {
      builder.buildComponent(ComponentRType::Gravity {});
    }
    if (payload.blueprint.hitbox) {
      builder.buildComponent(ComponentRType::Hitbox {});
    }
    auto entity = builder.getResult();
    m_entities.push_back(entity);
    return entity;
  }

} // GameEngine::Entity
