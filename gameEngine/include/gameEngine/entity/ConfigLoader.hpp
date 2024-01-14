//
// Created by Alexandre Decobert on 08/01/2024.
//

#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include "gameEngine/entity/EntityFactory.hpp"

namespace GameEngine::Entity
{
  using json = nlohmann::json;

  class ConfigLoader {
   public:
    ConfigLoader();
    ~ConfigLoader();
    void loadFromJson(const std::string &jsonFilePath);
    void loadEntitiesTemplate(GameEngine::Entity::EntityFactory &entityFactory);
    void loadEntities(GameEngine::Entity::EntityFactory &entityFactory);

    EntityTemplate parseComponents(const json &config);
    void tryParseComponents(
      const std::string &componentName,
      const std::string &keyComponent,
      Entity::EntityTemplate &entity,
      const json &config,
      void (ConfigLoader::*function)(Entity::EntityTemplate &entity, const json &config));

    void parseEntity(const json &config, GameEngine::Entity::EntityFactory &entityFactory);

    void parseTransform(Entity::EntityTemplate &entity, const json &config);
    void parseDisplayable(Entity::EntityTemplate &entity, const json &config);
    void parseControllable(Entity::EntityTemplate &entity, const json &config);
    void parseNetworkedEntity(Entity::EntityTemplate &entity, const json &config);
    void parseMetaData(GameEngine::Entity::EntityTemplate &entity, const json &config);
    void parsePosition(GameEngine::Entity::EntityTemplate &entity, const json &config);
    void parseGravity(GameEngine::Entity::EntityTemplate &entity, const json &config);
    void parseHitbox(GameEngine::Entity::EntityTemplate &entity, const json &config);
    void parseParallax(GameEngine::Entity::EntityTemplate &entity, const json &config);
    void parseHealth(GameEngine::Entity::EntityTemplate &entity, const json &config);

   private:
    json m_config;
  };
} // namespace GameEngine::Entity
