//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/scene/IScene.hpp"
#include "sceneController/HostGameController.hpp"

#include <memory>
#include <vector>

namespace Rtype::Scene
{
  class HostGame : public GameEngine::Scene::IScene {
   public:
    HostGame(SceneController::HostGameController &controller);

    void initRegistries() final;

    void initEntities() final;

    void initEvents() final;

    void onUpdate(size_t df) final;

    std::vector<GameEngine::ECS::Entity> getEntities();

   private:
    SceneController::HostGameController m_controller;

   private:
    std::vector<GameEngine::ECS::Entity> m_entities;          ///< Vector of entities in the game scene.
    std::shared_ptr<GameEngine::ECS::Registry> m_ecsRegistry; ///< Unique pointer to the ECS registry.
    std::unique_ptr<GameEngine::Event::EventRegistry>
      m_eventRegistry; ///< Unique pointer to the Event registry.
    std::shared_ptr<GameEngine::Entity::EntityFactory>
      m_entityFactory; ///< Unique pointer to the entity factory.
  };
} // namespace Client
