//
// Created by raphael on 12/22/23.
//

#pragma once
#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/scene/SimpleScene.hpp"

#include <memory>
#include <vector>

namespace Server::Game
{

  class RtypeScene : public GameEngine::Scene::SimpleScene {
   public:
    void initRegistries() final;

    void initEntities() final;

    std::vector<GameEngine::ECS::Entity> getEntities();

   private:
  };

} // namespace Server::Game::Rtype
