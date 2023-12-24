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
    void load() final;

  private:
    Rtype::RtypeScene m_scene;
  };
} // namespace Server::Game
