//
// Created by raphael on 12/23/23.
//

#pragma once

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include "gameEngine/network/serialize.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace ComponentRType
{

  struct MetaData : public GameEngine::Serialize::NetworkBaseSerializer {
    std::string name;

    MetaData() = default;
    explicit MetaData(std::string n)
      : name(std::move(n))
    {
    }

    void serialize(NetworkBaseSerializer::ArchiveO &ar, unsigned int const) const final
    {
      ar & name;
    }

    void deserialize(NetworkBaseSerializer::ArchiveI &ar, unsigned int const) final
    {
      ar & name;
    }
  };

  struct MetaDataTest : public GameEngine::Serialize::NetworkBaseSerializer {
    std::string name;
    int nbr = 0;

    MetaDataTest() = default;
    explicit MetaDataTest(std::string name, int nbr)
      : name(std::move(name))
      , nbr(nbr)
    {
    }

    void serialize(NetworkBaseSerializer::ArchiveO &ar, unsigned int const) const final
    {
      ar & name;
      ar & nbr;
    }

    void deserialize(NetworkBaseSerializer::ArchiveI &ar, unsigned int const) final
    {
      ar & name;
      ar & nbr;
    }
  };

} // namespace ComponentRType
