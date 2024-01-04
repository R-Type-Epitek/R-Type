//
// Created by Alexandre Decobert on 15/12/2023.
//

#pragma once

#include "constants/constants.hpp"
#include "gameEngine/network/Serializer.hpp"

#include <boost/serialization/base_object.hpp>
#include <utility>

using Vec3 = int;

namespace ComponentRType
{
  /// \brief A component representing the transformation properties of an entity.
  struct Transform : public GameEngine::Network::Serializer::BaseNetworkComponent {
    friend class boost::serialization::access;
    sf::Vector2f position;
    sf::Vector2f rotation;
    sf::Vector2f speed;
    sf::Vector2f movement;

    template<class Archive>
    void serialize(Archive &ar, unsigned int const)
    {
      ar &boost::serialization::base_object<GameEngine::Network::Serializer::BaseNetworkComponent>(*this);
      ar & position;
      ar & rotation;
      ar & speed;
      ar & movement;
    }
  };
} // namespace ComponentRType