//
// Created by raphael on 1/14/24.
//

#pragma once
#include "gameEngine/script/IScript.hpp"
#include "script/DataHolder.hpp"

namespace Rtype::Script
{
  class EnemyLinear : public DataHolder {
   public:
    explicit EnemyLinear(
      std::shared_ptr<GameEngine::ECS::Registry> ecsRegistry,
      std::shared_ptr<GameEngine::Event::EventRegistry> eventRegistry);

    void subscribeEvent() override;
    void execute(int df) override;
  };
} // namespace GameEngine::Script