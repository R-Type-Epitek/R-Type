//
// Created by raphael on 12/23/23.
//

#pragma once

#include "gameEngine/network/Serializer.hpp"
#include <cstdlib>
#include <string>
#include <utility>

namespace ComponentRType
{

  struct MetaData : public GameEngine::Network::Serializer::BaseNetworkComponent {
    std::string name;

    MetaData() = default;
    explicit MetaData(std::string n)
      : name(std::move(n))
    {
    }

  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &archive, const unsigned int)
    {
      archive &boost::serialization::base_object<GameEngine::Network::Serializer::BaseNetworkComponent>(
        *this);
      archive & name;
    }
  };

} // namespace ComponentRType
