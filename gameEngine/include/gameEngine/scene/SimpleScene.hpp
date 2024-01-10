//
// Created by raphael on 1/9/24.
//

#pragma once

//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/event/EventRegistry.hpp"
#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/scene/IScene.hpp"

#include <memory>
#include <vector>

namespace GameEngine::Scene
{
  /**
     * @brief SimpleScene class specifically designed for game functionality in an application.
     *
     * SimpleScene interface provide functionalities specific to game scenes,
     * including initialization of the ECS registry, entities, events and custom systems.
     */
  class SimpleScene : public GameEngine::Scene::IScene {
   public:
    void initRegistries() override;

    void initEntities() override;

    void initEvents() override;

    ECS::Registry& getEcsRegistry() override;

    std::shared_ptr<ECS::Registry> getSharedEcsRegistry() override;

    Event::EventRegistry& getEventRegistry() override;

    const std::vector<ECS::Entity>& getEntities() override;

    Entity::EntityFactory& getEntityFactory() override;

    void onUpdate(size_t df) override;

   protected:
    std::vector<ECS::Entity> m_entities;                    ///< Vector of entities in the game scene.
    std::shared_ptr<ECS::Registry> m_ecsRegistry;           ///< Unique pointer to the ECS registry.
    std::unique_ptr<Event::EventRegistry> m_eventRegistry;  ///< Unique pointer to the Event registry.
    std::shared_ptr<Entity::EntityFactory> m_entityFactory; ///< Unique pointer to the entity factory.
  };
} // namespace Client
