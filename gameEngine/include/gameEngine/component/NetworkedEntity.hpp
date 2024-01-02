//
// Created by raphael on 12/28/23.
//

#pragma once
#include "gameEngine/network/Serializer.hpp"

#include <cstddef>

namespace ComponentRType
{

  struct NetworkedEntity : public GameEngine::Network::Serializer::BaseNetworkComponent {
    size_t id;

    NetworkedEntity() = default;
    explicit NetworkedEntity(size_t id)
      : id(id)
    {
    }

    friend bool operator==(const NetworkedEntity &lhs, const NetworkedEntity &rhs)
    {
      return lhs.id == rhs.id;
    }

   private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &archive, const unsigned int)
    {
      archive &boost::serialization::base_object<GameEngine::Network::Serializer::BaseNetworkComponent>(
        *this);
      archive & id;
    }
  };

} // namespace ComponentRType
