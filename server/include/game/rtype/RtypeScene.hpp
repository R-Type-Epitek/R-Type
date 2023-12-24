//
// Created by raphael on 12/22/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/scene/IScene.hpp"
#include <memory>
#include <vector>

namespace Server::Game::Rtype
{

  class RtypeScene : public GameEngine::Scene::IScene {
  public:
    void initRegistry() final;

    void initEntities() final;

    GameEngine::ECS::Registry& getECS() final;

    void serializeEntities();

  private:
    std::vector<GameEngine::ECS::Entity> m_entities;
    std::unique_ptr<GameEngine::ECS::Registry> m_registry;
  };

} // namespace Server::Game::Rtype
