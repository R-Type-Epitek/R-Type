//
// Created by raphael on 12/23/23.
//

#pragma once
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace GameEngine::Serialize
{
  class NetworkBaseSerializer {
  public:
    virtual ~NetworkBaseSerializer() = default;

    using ArchiveO = boost::archive::text_oarchive;
    using ArchiveI = boost::archive::text_iarchive;

    virtual void serialize(ArchiveO &ar, unsigned int const version) const = 0;
    virtual void deserialize(ArchiveI &ar, unsigned int const version) = 0;
  };
} // namespace GameEngine::Serialize
