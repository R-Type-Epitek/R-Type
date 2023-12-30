//
// Created by raphael on 12/21/23.
//

#pragma once
#include "RTypeClient.hpp"

namespace Client
{
  class GameScene : public GameEngine::Scene::IScene {
   public:
    GameScene(Network& network);

    void initRegistry() final;

    void initEntities() final;

    GameEngine::ECS::Registry& getECS() final;

   protected:
    void initCustomSystem();

   private:
    std::vector<GameEngine::ECS::Entity> m_entities;
    std::unique_ptr<GameEngine::ECS::Registry> m_registry;
    Network& m_network;
  };
} // namespace Client
