//
// Created by Alexandre Decobert on 15/12/2023.
//

#pragma once

#include "gameEngine/network/Serializer.hpp"

#include <boost/serialization/base_object.hpp>
#include <utility>

using Vec3 = int;

namespace ComponentRType
{
  static const float defaultSpeed = 10.F;

  /// \brief A component representing the transformation properties of an entity.
  struct Transform : public GameEngine::Network::Serializer::BaseNetworkComponent {
    friend class boost::serialization::access;
    float speed = defaultSpeed;
    sf::Vector2f movement;
    sf::Vector2f rotation;

    template<class Archive>
    void serialize(Archive &ar, unsigned int const)
    {
      boost::serialization::base_object<GameEngine::Network::Serializer::BaseNetworkComponent>(*this);
      ar &(rotation);
      ar &(speed);
      ar &(movement);
    }
  };
} // namespace ComponentRType