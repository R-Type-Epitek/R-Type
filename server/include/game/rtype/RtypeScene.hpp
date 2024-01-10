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

  class RtypeScene : public GameEngine::Scene::IScene {
   public:
    void initRegistries() override;

    void initEntities() override;

    GameEngine::ECS::Registry& getEcsRegistry() override;

    std::shared_ptr<GameEngine::ECS::Registry> getSharedEcsRegistry() override;

    GameEngine::Event::EventRegistry& getEventRegistry() override;

    GameEngine::Entity::EntityFactory& getEntityFactory() override;

    std::vector<GameEngine::ECS::Entity> getEntities();

   private:
    std::vector<GameEngine::ECS::Entity> m_entities;          ///< Vector of entities in the game scene.
    std::shared_ptr<GameEngine::ECS::Registry> m_ecsRegistry; ///< Unique pointer to the ECS registry.
    std::unique_ptr<GameEngine::Event::EventRegistry>
      m_eventRegistry; ///< Unique pointer to the Event registry.
    std::shared_ptr<GameEngine::Entity::EntityFactory>
      m_entityFactory; ///< Unique pointer to the entity factory.
  };

} // namespace Server::Game::Rtype
