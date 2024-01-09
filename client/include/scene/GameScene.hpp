//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/scene/SimpleScene.hpp"
#include "network/Network.hpp"

#include <memory>
#include <vector>

namespace Client
{
  /**
   * @brief Scene class specifically designed for game functionality in a client application.
   *
   * GameScene extends the IScene interface to provide functionalities specific to game scenes,
   * including initialization of the ECS registry, entities, and custom systems. It also
   * integrates with the network for game-related communications.
   */
  class GameScene : public GameEngine::Scene::SimpleScene {
   public:
    explicit GameScene(Network& network);

    void initEntities() final;
    void initRegistries() final;

   protected:
    void initCustomSystem();

   private:
    Network& m_network;
  };
} // namespace Client
