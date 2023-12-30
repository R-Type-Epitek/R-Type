//
// Created by raphael on 12/24/23.
//

#pragma once

#include <SFML/System/Vector2.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace ComponentRType
{

  struct Movement2d {
    sf::Vector2f movement;

    template<class Archive>
    void serialize(Archive& ar, unsigned int const version)
    {
      ar& movement;
    }
  };

} // namespace ComponentRType
