//
// Created by raphael on 12/24/23.
//

#pragma once

#include "gameEngine/network/Serializer.hpp"
#include <boost/serialization/base_object.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>

namespace ComponentRType
{

  struct Position : public GameEngine::Network::Serializer::BaseNetworkComponent {
    friend class boost::serialization::access;

    sf::Vector2f position;

    template<class Archive>
    void serialize(Archive &archive, const unsigned int)
    {
      archive &boost::serialization::base_object<GameEngine::Network::Serializer::BaseNetworkComponent>(
        *this);
      archive & position;
    }
  };

} // namespace ComponentRType
