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
    GameEngine::Entity::ComponentsBluePrint bluePrint;

    MetaData() = default;

    explicit MetaData(GameEngine::Entity::ComponentsBluePrint bluePrint)
      : bluePrint(bluePrint)
    {
    }

    template<class Archive>
    void serialize(Archive &archive, const unsigned int)
    {
      boost::serialization::base_object<GameEngine::Network::Serializer::BaseNetworkComponent>(*this);
      archive &BOOST_SERIALIZATION_NVP(bluePrint);
    }
  };

} // namespace ComponentRType
