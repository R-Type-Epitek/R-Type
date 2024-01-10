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
      Background,
      Enemy,
      Boss,
      Bullet
    };

    static EntityType getEntityType(const std::string& typeStr) {
      static const std::unordered_map<std::string, EntityType> typeMap = {
        {"None", None},
        {"Player", Player},
        {"Asteroid", Asteroid},
        {"Background", Background},
        {"Enemy", Enemy},
        {"Bullet", Bullet},
        {"Boss", Boss}};

      auto it = typeMap.find(typeStr);
      assert(it != typeMap.end());
      return it->second;
    }

    static std::string getEntityType(const EntityType& type) {
      static const std::unordered_map<EntityType, std::string> typeMap = {
        {None, "None"},
        {Player, "Player"},
        {Asteroid, "Asteroid"},
        {Background, "Background"},
        {Enemy, "Enemy"},
        {Bullet, "Bullet"},
        {Boss, "Boss"}
      };

      auto it = typeMap.find(type);
      assert(it != typeMap.end());
      return it->second;
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
};

struct EntityBluePrint {
  bool light = true;
  std::string defaultAssetPath = "";
  ComponentBluePrint blueprint;
};

using EntityType = EntityTypeHelper::EntityType;
} // namespace GameEngine::Entity
