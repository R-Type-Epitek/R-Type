//
// Created by raphael on 12/22/23.
//

#pragma once
#include "game/IGame.hpp"
#include "RtypeScene.hpp"
#include <iostream>

namespace Server::Game
{

  class RtypeGame : public IGame {
   public:
    RtypeGame() = default;
    ~RtypeGame() = default;

    RtypeGame(const RtypeGame &)
    {
    }

    void load() final;
    std::vector<std::vector<char>> getEntities() final;
    void pushEvent(Event event, Player player)
    {
      std::cout << "pushEvent: " << static_cast<int>(event) << "by player (" << player.id << ") with name "
                << player.name << std::endl;
    };

   private:
    Server::Game::RtypeScene m_scene;
  };
} // namespace Server::Game
