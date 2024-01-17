//
// Created by Alexandre Decobert on 08/01/2024.
//

#include "gameEngine/entity/ConfigLoader.hpp"
#include <fstream>
#include <random>
#include <iostream>
#include "gameEngine/entity/EntityFactory.hpp"
#include "spdlog/spdlog.h"

namespace GameEngine::Entity
{

  ConfigLoader::ConfigLoader()
  {
  }

  ConfigLoader::~ConfigLoader()
  {
  }

  void ConfigLoader::loadFromJson(const std::string &jsonFilePath)
  {
    std::ifstream file(jsonFilePath);
    if (!file.is_open()) {
      spdlog::error("Could not open file {}", jsonFilePath);
      throw std::runtime_error("Could not open file " + jsonFilePath);
    }

    try {
      file >> m_config;
    } catch (const std::exception &e) {
      spdlog::error("Error parsing JSON: {}", jsonFilePath);
      std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
  }

  void ConfigLoader::loadEntities(GameEngine::Entity::EntityFactory &entityFactory)
  {
    if (m_config.contains("entities") && m_config["entities"].is_array()) {
      for (const auto &element : m_config["entities"]) {
        parseEntity(element, entityFactory);
      }
    }
  }

  void ConfigLoader::parseEntity(const json &config, GameEngine::Entity::EntityFactory &entityFactory)
  {
    std::string typeStr = config["type"];
    std::string baseTypeStr = config.value("baseType", "");
    std::string type = baseTypeStr.empty() ? typeStr : baseTypeStr;

    EntityTemplate entityTemplate = entityFactory.getEntityTemplate(type);
    entityTemplate.networkedEntity = ComponentRType::NetworkedEntity {EntityFactory::idOffset};
    entityTemplate.metaData.bluePrint = entityTemplate.blueprint;

    if (config.contains("position")) {
      int x = config["position"].value("x", 0);
      int y = config["position"].value("y", 0);
      entityTemplate.position.position = {static_cast<float>(x), static_cast<float>(y)};
    }
    if (config.contains("speed") && entityTemplate.blueprint.transform) {
      entityTemplate.transform.speed = config["speed"];
    }
    if (config.contains("scriptName") && entityTemplate.blueprint.scriptable) {
      entityTemplate.scriptable.scriptName = config["scriptName"];
    }
    if (config.contains("health") && entityTemplate.blueprint.health) {
      entityTemplate.health.value = config["health"];
    }

    entityFactory.createFromTemplate(entityTemplate);
    EntityFactory::idOffset++;
  }

  void ConfigLoader::loadEntitiesTemplate(GameEngine::Entity::EntityFactory &entityFactory)
  {
    if (m_config.contains("entityTemplate") && m_config["entityTemplate"].is_array()) {
      for (const auto &element : m_config["entityTemplate"]) {
        if (!element.contains("typeName") || !element.contains("components")) {
          spdlog::error("Error: entityTemplate must have a typeName and components");
          throw std::runtime_error("Error: entityTemplate must have a typeName and components");
        }
        EntityTemplate entityTemplate = parseComponents(element["components"]);
        entityFactory.addEntityTemplate(element["typeName"], entityTemplate);
      }
    }
  }
  EntityTemplate ConfigLoader::parseComponents(const json &config)
  {
    EntityTemplate entityTplt;
    if (!config.is_array()) {
      spdlog::error("Error: components must be an array of objects");
      throw std::runtime_error("Error: components must be an array of objects");
    }
    for (const auto &element : config) {
      if (!element.is_object()) {
        spdlog::error("Error: components must be an object");
        throw std::runtime_error("Error: components must be an object");
      }
      std::string name = element["name"];
      tryParseComponents(name, "Transform", entityTplt, element, &ConfigLoader::parseTransform);
      tryParseComponents(name, "Displayable", entityTplt, element, &ConfigLoader::parseDisplayable);
      tryParseComponents(name, "Controllable", entityTplt, element, &ConfigLoader::parseControllable);
      tryParseComponents(name, "NetworkedEntity", entityTplt, element, &ConfigLoader::parseNetworkedEntity);
      tryParseComponents(name, "MetaData", entityTplt, element, &ConfigLoader::parseMetaData);
      tryParseComponents(name, "Position", entityTplt, element, &ConfigLoader::parsePosition);
      tryParseComponents(name, "Gravity", entityTplt, element, &ConfigLoader::parseGravity);
      tryParseComponents(name, "Hitbox", entityTplt, element, &ConfigLoader::parseHitbox);
      tryParseComponents(name, "Parallax", entityTplt, element, &ConfigLoader::parseParallax);
      tryParseComponents(name, "Health", entityTplt, element, &ConfigLoader::parseHealth);
      tryParseComponents(name, "Scriptable", entityTplt, element, &ConfigLoader::parseScriptable);
    }
    return entityTplt;
  }

  void ConfigLoader::tryParseComponents(
    const std::string &componentName,
    const std::string &keyComponent,
    Entity::EntityTemplate &entity,
    const json &config,
    void (ConfigLoader::*function)(Entity::EntityTemplate &entity, const json &config))
  {
    if (keyComponent == componentName) {
      (this->*function)(entity, config);
    }
  }

  void ConfigLoader::parseTransform(EntityTemplate &entity, const json &config)
  {
    entity.blueprint.transform = true;
    int speed = config.value("speed", ComponentRType::defaultSpeed);
    entity.transform.speed = speed;

    if (config.contains("movement")) {
      int x = config["movement"].value("x", 0);
      int y = config["movement"].value("y", 0);

      entity.transform.movement = {static_cast<float>(x), static_cast<float>(y)};
    }
  }

  void ConfigLoader::parseDisplayable(EntityTemplate &entity, const json &config)
  {
    entity.blueprint.displayable = true;
    std::string assetPath = config.value("assetPath", "");
    entity.displayable.assetPath = assetPath;

    if (!config.contains("rect")) {
      entity.displayable = ComponentRType::Displayable(assetPath);
      return;
    }
    int rectX = config["rect"].value("x", -1);
    int rectY = config["rect"].value("y", -1);
    int rectWidth = config["rect"].value("width", -1);
    int rectHeight = config["rect"].value("height", -1);
    entity.displayable = ComponentRType::Displayable(assetPath, {rectX, rectY, rectWidth, rectHeight});
  }

  void ConfigLoader::parseControllable(EntityTemplate &entity, const json &)
  {
    entity.blueprint.controllable = true;
  }

  void ConfigLoader::parseNetworkedEntity(EntityTemplate &entity, const json &)
  {
    entity.blueprint.networkedEntity = true;
  }

  void ConfigLoader::parseMetaData(EntityTemplate &entity, const json &)
  {
    entity.blueprint.metaData = true;
  }

  void ConfigLoader::parsePosition(EntityTemplate &entity, const json &config)
  {
    entity.blueprint.position = true;
    int x = config["position"].value("x", 0);
    int y = config["position"].value("y", 0);
    entity.position.position = {static_cast<float>(x), static_cast<float>(y)};
    entity.position.latestPosition = {static_cast<float>(x), static_cast<float>(y)};
  }

  void ConfigLoader::parseGravity(EntityTemplate &entity, const json &)
  {
    entity.blueprint.gravity = true;
  }

  void ConfigLoader::parseHitbox(EntityTemplate &entity, const json &config)
  {
    entity.blueprint.hitbox = true;
    int mask = config.value("mask", 0);
    entity.hitbox.mask = mask;
  }

  void ConfigLoader::parseParallax(EntityTemplate &entity, const json &)
  {
    entity.blueprint.parallax = true;
  }

  void ConfigLoader::parseHealth(EntityTemplate &entity, const json &config)
  {
    entity.blueprint.health = true;
    int health = config.value("health", 0);
    int damage = config.value("damage", ComponentRType::kdefaultDamage);
    bool isAlive = config.value("isAlive", true);
    entity.health.value = health;
    entity.health.isAlive = isAlive;
    entity.health.damage = damage;
  }

  void ConfigLoader::parseScriptable(EntityTemplate &entity, const json &config)
  {
    entity.blueprint.scriptable = true;
    std::string scriptName = config.value("scriptName", "");
    entity.scriptable.scriptName = scriptName;
  }

  void ConfigLoader::loadScripts(GameEngine::Entity::EntityFactory &entityFactory)
  {
    if (m_config.contains("entitiesScript") && m_config["entitiesScript"].is_array()) {
      for (const auto &element : m_config["entitiesScript"]) {
        parseScript(element, entityFactory.getScriptManager());
      }
    }
  }

  void ConfigLoader::parseScript(const json &config, Script::ScriptManager &scriptManager)
  {
    std::string name = config["name"];
    std::string baseScriptName = config["scriptName"];
    std::string scriptPath = config.value("scriptPath", "");

    scriptManager.addScriptBinding(name, baseScriptName);
  }

  void ConfigLoader::loadStages(EntityFactory &entityFactory)
  {
    if (m_config.contains("stages") && m_config["stages"].is_array()) {
      for (const auto &element : m_config["stages"]) {
        for (const auto &entities : element["entities"]) {
          parseStage(entities, entityFactory);
        }
      }
    }
  }

  void ConfigLoader::parseStage(const json &config, GameEngine::Entity::EntityFactory &entityFactory)
  {
    std::random_device rd;
    std::mt19937 gen(rd());

    try {
      std::string entityType = config.value("typeName", "");
      int number = config["number"];
      int maxX = config["range_x"].value("max", 0);
      int minX = config["range_x"].value("min", 0);
      int maxY = config["range_y"].value("max", 0);
      int minY = config["range_y"].value("min", 0);

      auto scheme = entityFactory.getEntityTemplate(entityType);
      for (int i = 0; i < number; i++) {
        EntityTemplate entityTemplate = scheme;
        entityTemplate.networkedEntity = ComponentRType::NetworkedEntity {EntityFactory::idOffset};
        EntityFactory::idOffset++;
        std::uniform_real_distribution<float> xDist(minX, maxX);
        std::uniform_real_distribution<float> yDist(minY, maxY);
        entityTemplate.position.position = {static_cast<float>(xDist(gen)), static_cast<float>(yDist(gen))};

        entityTemplate.metaData.bluePrint = entityTemplate.blueprint;
        entityFactory.createFromTemplate(entityTemplate);
      }
    } catch (const std::exception &e) {
      spdlog::error("Error parsing JSON: {}", e.what());
    }
  }

} // namespace GameEngine::Loader
