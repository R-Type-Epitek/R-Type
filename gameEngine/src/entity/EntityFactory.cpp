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

  size_t EntityFactory::idOffset = 2000;

  EntityFactory::EntityFactory(std::vector<GameEngine::ECS::Entity> &entities, ECS::Registry &registry)
    : m_entities(entities)
    , m_registry(registry)
  {
  }

  GameEngine::ECS::Entity EntityFactory::createFromNetwork(
    ComponentRType::NetworkedEntity &id,
    EntityTemplate &entityTemplate)
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

  GameEngine::ECS::Entity EntityFactory::createFromBluePrint(ComponentsBluePrint &bluePrint)
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

  GameEngine::ECS::Entity EntityFactory::createFromTemplate(EntityTemplate &entityTemplate)
  {
    auto builder = EntityBuilder(m_registry);
    if (entityTemplate.blueprint.transform) {
      builder.buildComponent(std::move(entityTemplate.transform));
    }
    if (entityTemplate.blueprint.controllable) {
      builder.buildComponent(std::move(entityTemplate.controllable));
    }
    if (entityTemplate.blueprint.networkedEntity) {
      builder.buildComponent(std::move(entityTemplate.networkedEntity));
    }
    if (entityTemplate.blueprint.metaData) {
      builder.buildComponent(std::move(entityTemplate.metaData));
    }
    if (entityTemplate.blueprint.position) {
      builder.buildComponent(std::move(entityTemplate.position));
    }
    if (entityTemplate.blueprint.gravity) {
      builder.buildComponent(std::move(entityTemplate.gravity));
    }
    if (entityTemplate.blueprint.hitbox) {
      builder.buildComponent(std::move(entityTemplate.hitbox));
    }
    if (entityTemplate.blueprint.displayable) {
      auto &ref = entityTemplate.displayable;
      ref.sprite.setPosition(entityTemplate.position.position.x, entityTemplate.position.position.y);
      ComponentRType::Displayable newComponent(
        ref.assetPath,
        {ref.rectLeft, ref.rectTop, ref.rectWidth, ref.rectHeight});
      newComponent.sprite.setPosition(entityTemplate.position.position);
      builder.buildComponent(std::move(newComponent));
    }
    auto entity = builder.getResult();
    m_entities.push_back(entity);
    return entity;
  }

  GameEngine::ECS::Entity EntityFactory::createFromTemplateNetwork(EntityTemplate &entityTemplate)
  {
    entityTemplate.metaData.bluePrint = entityTemplate.blueprint;
    entityTemplate.networkedEntity.id = EntityFactory::idOffset++;
    return createFromTemplate(entityTemplate);
  }

  GameEngine::ECS::Entity EntityFactory::createFromTemplateName(const std::string &name)
  {
    auto scheme = getEntityTemplate(name);
    return createFromTemplate(scheme);
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
