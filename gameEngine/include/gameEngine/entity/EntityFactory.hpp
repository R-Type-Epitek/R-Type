//
// Created by raphael on 1/4/24.
//

#pragma once

#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Controllable.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Hitbox.hpp"
#include "gameEngine/component/Parallax.hpp"
#include "gameEngine/component/Scriptable.hpp"
#include "gameEngine/script/ScriptManager.hpp"
#include "EntityType.hpp"
#include "gameEngine/asset/AssetManager.hpp"
#include "spdlog/spdlog.h"
#include <map>
#include <stdexcept>

namespace GameEngine::Entity
{

  struct EntityTemplate {
    ComponentsBluePrint blueprint;
    ComponentRType::Transform transform;
    ComponentRType::Displayable displayable;
    ComponentRType::Controllable controllable;
    ComponentRType::NetworkedEntity networkedEntity;
    ComponentRType::MetaData metaData;
    ComponentRType::Position position;
    ComponentRType::Gravity gravity;
    ComponentRType::Hitbox hitbox;
    ComponentRType::Parallax parallax;
    ComponentRType::Scriptable scriptable;
  };

  class EntityFactory {
   public:
    EntityFactory(std::vector<GameEngine::ECS::Entity> &entities, GameEngine::ECS::Registry &registry);

    //    GameEngine::ECS::Entity create(const EntityType &type);

    GameEngine::ECS::Entity createFromNetwork(
      ComponentRType::NetworkedEntity &id,
      EntityTemplate &entityTemplate);

    GameEngine::ECS::Entity loadFromNetwork(
      ComponentRType::NetworkedEntity &networkId,
      ComponentRType::MetaData &metaData);

    GameEngine::ECS::Entity createFromBluePrint(ComponentsBluePrint &bluePrint);
    GameEngine::ECS::Entity createFromTemplate(EntityTemplate &entityTemplate);
    GameEngine::ECS::Entity createFromTemplateNetwork(EntityTemplate &entityTemplate);
    GameEngine::ECS::Entity createFromTemplateName(const std::string &name);

    std::map<std::string, EntityTemplate> &getEntitiesTemplate();
    void addEntityTemplate(const std::string &name, const EntityTemplate &entityTemplate);
    EntityTemplate getEntityTemplate(const std::string &name);
    bool entityTemplateExist(const std::string &name);

    Script::ScriptManager &getScriptManager();

    static size_t idOffset;

   private:
    using AssetManager = GameEngine::Asset::AssetManager;

    Script::ScriptManager m_scriptManager;
    std::map<std::string, EntityTemplate> m_entitiesTemplate;
    std::vector<GameEngine::ECS::Entity> &m_entities; ///< Vector of entities in the Factory context.
    GameEngine::ECS::Registry &m_registry;            ///< Reference to the ECS registry.
  };
} // GameEngine::Entity