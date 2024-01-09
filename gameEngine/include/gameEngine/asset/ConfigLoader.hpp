//
// Created by Alexandre Decobert on 08/01/2024.
//

#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <assert.h>
#include <fstream>
#include <vector>
#include "gameEngine/entity/EntityFactory.hpp"

using json = nlohmann::json;

class ConfigLoader {
 public:
  ConfigLoader();
  ~ConfigLoader();
  static void loadEntities(std::shared_ptr<GameEngine::Entity::EntityFactory> &entityFactory);
 private:
  static void openConfigFile();
  static nlohmann::json m_config;
};