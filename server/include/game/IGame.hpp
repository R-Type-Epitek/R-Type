//
// Created by raphael on 12/22/23.
//

#pragma once

#include <vector>
namespace Server::Game
{
  class IGame {
   public:
    virtual ~IGame() = default;

    virtual void load() = 0;

    virtual std::vector<std::vector<char>> getEntities() = 0;
  };

} // namespace Server::Game