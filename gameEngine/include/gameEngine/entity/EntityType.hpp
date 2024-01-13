//
// Created by raphael on 1/4/24.
//

#pragma once
#include "gameEngine/network/Serializer.hpp"
#include <boost/serialization/access.hpp>

namespace GameEngine::Entity
{

  struct ComponentsBluePrint : public GameEngine::Network::Serializer::BaseNetworkComponent {
    friend class boost::serialization::access;
    ComponentsBluePrint() = default;
    template<class Archive>
    void serialize(Archive &archive, const unsigned int)
    {
      archive &boost::serialization::base_object<GameEngine::Network::Serializer::BaseNetworkComponent>(
        *this);
      archive & transform;
      archive & displayable;
      archive & clickable;
      archive & controllable;
      archive & networkedEntity;
      archive & metaData;
      archive & position;
      archive & gravity;
      archive & hitbox;
    }

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

} // namespace GameEngine::Entity
