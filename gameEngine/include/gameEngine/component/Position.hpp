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
    sf::Vector2f latestPosition;
    sf::Vector2f latestValidPosition;
    bool isValid = true;

    Position() = default;

    explicit Position(float x, float y)
      : position(x, y)
      , latestPosition(x, y)
      , latestValidPosition(x, y)
    {
    }

    template<class Archive>
    void serialize(Archive &archive, const unsigned int)
    {
      boost::serialization::base_object<GameEngine::Network::Serializer::BaseNetworkComponent>(*this);
      archive &BOOST_SERIALIZATION_NVP(position);
      archive &BOOST_SERIALIZATION_NVP(latestPosition);
      archive &BOOST_SERIALIZATION_NVP(latestValidPosition);
      archive &BOOST_SERIALIZATION_NVP(isValid);
    }
  };

} // namespace ComponentRType
