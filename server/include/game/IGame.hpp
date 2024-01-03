//
// Created by raphael on 12/22/23.
//

#pragma once

#include <cstddef>
#include <vector>
#include <string>

namespace Server::Game
{
  struct Player {
    size_t id;
    std::string name = ""; // optional only needed for Connection
    // GameEngine::Keyboard::Key = None;
  };

  enum class Event
  {
    Input,
    Connect,
    Disconnect,
  };

  class IGame {
   public:
    virtual ~IGame() = default;

    virtual void load() = 0;

    virtual std::vector<std::vector<char>> getEntities() = 0;

    virtual void pushEvent(Event, Player) = 0;
  };
} // namespace Server::Game
