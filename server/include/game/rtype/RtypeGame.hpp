//
// Created by raphael on 12/22/23.
//

#pragma once
#include "../IGame.hpp"
#include "RtypeScene.hpp"
#include "game/IGame.hpp"

namespace Server::Game
{

  class RtypeGame : public IGame {
   public:
    RtypeGame() = default;
    ~RtypeGame() = default;

    RtypeGame(const RtypeGame& other)
    {
    }

    void load() final;
    std::vector<std::vector<char>> getEntities() final;

   private:
    Server::Game::RtypeScene m_scene;
  };
} // namespace Server::Game
