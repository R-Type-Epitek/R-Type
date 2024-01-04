//
// Created by raphael on 12/23/23.
//

#pragma once

#include "gameEngine/network/Serializer.hpp"
#include "gameEngine/entity/EntityType.hpp"

#include <boost/serialization/access.hpp>
#include <cstdlib>
#include <string>
#include <utility>

namespace ComponentRType
{

  struct MetaData : public GameEngine::Network::Serializer::BaseNetworkComponent {
    friend class boost::serialization::access;
    std::string texturePath;
    GameEngine::Entity::EntityType entityType = GameEngine::Entity::EntityType::Player;

    MetaData() = default;
    explicit MetaData(std::string path, GameEngine::Entity::EntityType type)
      : texturePath(std::move(path))
      , entityType(type)
    {
    }

    template<class Archive>
    void serialize(Archive &archive, const unsigned int)
    {
      archive &boost::serialization::base_object<GameEngine::Network::Serializer::BaseNetworkComponent>(
        *this);
      archive & texturePath;
      archive & entityType;
    }
  };

} // namespace ComponentRType
