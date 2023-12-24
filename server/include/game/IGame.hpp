//
// Created by raphael on 12/22/23.
//

#pragma once

namespace Server::Game
{
  class IGame {
  public:
    virtual ~IGame() = default;

    virtual void load() = 0;
  };

} // namespace Server::Game