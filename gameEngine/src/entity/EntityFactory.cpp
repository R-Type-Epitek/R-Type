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
#include "spdlog/spdlog.h"

namespace GameEngine::Entity
{

  EntityFactory::EntityFactory(std::vector<GameEngine::ECS::Entity> &entities, ECS::Registry &registry)
    : m_entities(entities)
    , m_registry(registry)
  {
  }

  GameEngine::ECS::Entity EntityFactory::createFromNetwork(
    ComponentRType::NetworkedEntity &id,
    const EntityTemplate &entityTemplate)
  {
    spdlog::info("[EntityFactory] Creating entity from Network...");
    auto &componentManager = m_registry.getComponentManager();
    auto entity = createFromTemplate(entityTemplate);
    componentManager->getComponent<ComponentRType::NetworkedEntity>(entity) = id;
    componentManager->getComponent<ComponentRType::MetaData>(entity).bluePrint = entityTemplate.blueprint;

    return entity;
  }

  GameEngine::ECS::Entity EntityFactory::loadFromNetwork(
    ComponentRType::NetworkedEntity &id,
    ComponentRType::MetaData &metaData)
  {
    spdlog::info("[EntityFactory] Creating entity from Network...");
    auto &componentManager = m_registry.getComponentManager();
    auto entity = createFromBluePrint(metaData.bluePrint);

    componentManager->getComponent<ComponentRType::MetaData>(entity) = metaData;
    componentManager->getComponent<ComponentRType::NetworkedEntity>(entity) = id;
    return entity;
  }

  GameEngine::ECS::Entity EntityFactory::createFromBluePrint(ComponentsBluePrint const &bluePrint)
  {
    spdlog::info("[EntityFactory] Creating entity from BluePrint...");

    auto builder = EntityBuilder(m_registry);
    if (bluePrint.transform) {
      builder.buildComponent(ComponentRType::Transform {});
    }
    if (bluePrint.displayable) {
      builder.buildComponent(ComponentRType::Displayable());
    }
    if (bluePrint.clickable) {
      builder.buildComponent(ComponentRType::Clickable {});
    }
    if (bluePrint.controllable) {
      builder.buildComponent(ComponentRType::Controllable {});
    }
    if (bluePrint.networkedEntity) {
      builder.buildComponent(ComponentRType::NetworkedEntity {});
    }
    if (bluePrint.metaData) {
      builder.buildComponent(ComponentRType::MetaData {});
    }
    if (bluePrint.position) {
      builder.buildComponent(ComponentRType::Position {});
    }
    if (bluePrint.gravity) {
      builder.buildComponent(ComponentRType::Gravity {});
    }
    if (bluePrint.hitbox) {
      builder.buildComponent(ComponentRType::Hitbox {});
    }
    auto entity = builder.getResult();
    m_entities.push_back(entity);
    return entity;
  }

  GameEngine::ECS::Entity EntityFactory::createFromTemplate(const EntityTemplate &entityTemplate)
  {
    auto builder = EntityBuilder(m_registry);
    if (entityTemplate.blueprint.transform) {
      builder.buildComponent(entityTemplate.transform);
    }
    if (entityTemplate.blueprint.displayable) {
      auto &ref = entityTemplate.displayable;
      builder.buildComponent(ComponentRType::Displayable(
        ref.assetPath,
        {ref.rectLeft, ref.rectTop, ref.rectWidth, ref.rectHeight}));
    }
    if (entityTemplate.blueprint.controllable) {
      builder.buildComponent(entityTemplate.controllable);
    }
    if (entityTemplate.blueprint.networkedEntity) {
      builder.buildComponent(entityTemplate.networkedEntity);
    }
    if (entityTemplate.blueprint.metaData) {
      builder.buildComponent(entityTemplate.metaData);
    }
    if (entityTemplate.blueprint.position) {
      builder.buildComponent(entityTemplate.position);
    }
    if (entityTemplate.blueprint.gravity) {
      builder.buildComponent(entityTemplate.gravity);
    }
    if (entityTemplate.blueprint.hitbox) {
      builder.buildComponent(entityTemplate.hitbox);
    }
    auto entity = builder.getResult();
    m_entities.push_back(entity);
    return entity;
  }

  std::map<std::string, EntityTemplate> &EntityFactory::getEntitiesTemplate()
  {
    return m_entitiesTemplate;
  }

  void EntityFactory::addEntityTemplate(const std::string &name, const EntityTemplate &entityTemplate)
  {
    m_entitiesTemplate[name] = entityTemplate;
  }

  EntityTemplate EntityFactory::getEntityTemplate(const std::string &name)
  {
    if (!entityTemplateExist(name)) {
      spdlog::error("[EntityFactory] Entity template {} does not exist", name);
      throw std::runtime_error("Entity template " + name + " does not exist");
    }
    return m_entitiesTemplate.at(name);
  }

  bool EntityFactory::entityTemplateExist(const std::string &name)
  {
    return m_entitiesTemplate.find(name) != m_entitiesTemplate.end();
  }

} // GameEngine::Entity
