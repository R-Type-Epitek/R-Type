//
// Created by raphael on 1/4/24.
//

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <SFML/System/Vector2.hpp>

namespace GameEngine::Entity
{
  struct EntityTypeHelper {
    enum EntityType
    {
      None,
      Player,
      Asteroid,
      Enemy,
      Boss,
      Bullet
    };

    static EntityType getEntityTypeFromString(const std::string& typeStr)
    {
      static const std::unordered_map<std::string, EntityType> typeMap = {
        {"None", None},
        {"Player", Player},
        {"Asteroid", Asteroid},
        {"Enemy", Enemy},
        {"Bullet", Bullet},
        {"Boss", Boss}};

      auto it = typeMap.find(typeStr);
      if (it != typeMap.end()) {
        return it->second;
      } else {
        std::cerr << "Error: Unknown entity type '" << typeStr << "'" << std::endl;
        throw std::invalid_argument("Unknown entity type");
      }
    }
  };

  struct ComponentBluePrint {
    bool transform = false;
    bool displayable = false;
    bool clickable = false;
    bool controllable = false;
    bool networkedEntity = false;
    bool metaData = false;
    bool position = false;
    bool gravity = false;
    bool hitbox = false;
  };

  struct EntityBluePrint {
    bool light = true;
    std::string defaultAssetPath = "";
    ComponentBluePrint blueprint;
  };

  using EntityType = EntityTypeHelper::EntityType;
} // namespace GameEngine::Entity
