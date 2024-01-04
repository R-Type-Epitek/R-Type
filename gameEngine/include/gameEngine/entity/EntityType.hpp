//
// Created by raphael on 1/4/24.
//

#pragma once
#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>

namespace GameEngine::Entity
{
  enum EntityType
  {
    None,
    Player,
    Enemy,
    Bullet
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

} // namespace GameEngine::Entity
