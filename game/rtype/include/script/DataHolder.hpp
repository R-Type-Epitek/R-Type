//
// Created by raphael on 1/14/24.
//

#pragma once
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/script/IScript.hpp"

namespace Rtype::Script
{
  class DataHolder : public GameEngine::Script::IScript {
   public:
    DataHolder(
      std::shared_ptr<GameEngine::ECS::Registry> ecsRegistry,
      std::shared_ptr<GameEngine::Event::EventRegistry> eventRegistry);
    void subscribeEvent() override = 0;
    void execute(int df) override = 0;

    bool isConfigured() final;
    void attachEntity(const GameEngine::ECS::Entity entity) override;
    void attachEcsRegistry(std::shared_ptr<GameEngine::ECS::Registry> ecsRegistry) override;
    void attachEventRegistry(std::shared_ptr<GameEngine::Event::EventRegistry> eventRegistry) override;

    GameEngine::ECS::Entity m_entity;
    std::shared_ptr<GameEngine::ECS::Registry> m_ecsRegistry;
    std::shared_ptr<GameEngine::Event::EventRegistry> m_eventRegistry;
  };
} // namespace GameEngine::Script