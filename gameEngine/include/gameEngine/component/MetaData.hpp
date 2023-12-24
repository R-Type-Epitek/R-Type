//
// Created by raphael on 12/23/23.
//

#pragma once

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace ComponentRType
{

  struct MetaData {
    std::string name;

    template<class Archive>
    void serialize(Archive& ar, unsigned int const version)
    {
      ar& name;
    }
  };

} // namespace ComponentRType
