//
// Created by raphael on 12/22/23.
//

#include "game/rtype/RtypeGame.hpp"

namespace Server::Game
{

  void RtypeGame::load()
  {
    m_scene.initRegistry();
    m_scene.initEntities();
  }

} // namespace Server::Game