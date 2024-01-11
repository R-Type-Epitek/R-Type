//
// Created by Alexandre Decobert on 08/01/2024.
//

#include "gameEngine/asset/ConfigLoader.hpp"

nlohmann::json ConfigLoader::m_config;

ConfigLoader::ConfigLoader()
{
}

ConfigLoader::~ConfigLoader()
{
}

void ConfigLoader::openConfigFile()
{
  std::ifstream file("game/rtype/config/config.json");
  if (!file.is_open()) {
    std::cerr << "Error: cannot open config.json" << std::endl;
    exit(84);
  }
  file >> m_config;
  file.close();
}

void ConfigLoader::loadEntities(std::shared_ptr<GameEngine::Entity::EntityFactory> &entityFactory)
{
  if (m_config.empty()) {
    openConfigFile();
  }
  u_int16_t id = 3000;

  for (const auto &enemyType : m_config["enemyTypes"]) {
    if (!enemyType.is_object()) {
      std::cerr << "Error: enemyTypes must be an array of objects" << std::endl;
      exit(84);
    }
    std::string type_str = enemyType["type"];
    auto entityType = GameEngine::Entity::EntityTypeHelper::getEntityTypeFromString(type_str);
    std::string path = enemyType.value("path", "game/rtype/assets/sprites/r-typesheet23.gif");
    auto compMetaData = ComponentRType::MetaData(path, entityType);
    auto compId = ComponentRType::NetworkedEntity {id};
    entityFactory->createFromNetwork(compId, compMetaData);
    id++;
  }
}