//
// Created by raphael on 1/10/24.
//

#pragma once
#include "IGame.hpp"
#include "gameEngine/core/Core.hpp"
#include <memory>
#include <string>

namespace Server::Game
{
  class Game : public IGame {
   public:
    Game() = default;

    void load() final;

    void initScenes();

    std::vector<std::vector<char>> getSerializedEntities() final;

    void update(unsigned int df) final;

    void pushEvent(Event event, Player player) final;

   private:
    std::unique_ptr<GameEngine::Core::Core> m_coreGE;
  };
} // namespace Server