//
// Created by raphael on 12/20/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/event/EventRegistry.hpp"

namespace GameEngine::Scene
{
  /**
   * @brief IScene class specifically designed for game functionality in an application.
   *
   * IScene interface provide functionalities specific to game scenes,
   * including initialization of the ECS registry, entities, events and custom systems.
   */
  class IScene {
   public:
    /**
     * @brief Destroy the IScene object.
     *
     */
    virtual ~IScene() = default;

    /**
     * @brief Initialize the ECS registry for the game scene.
     */
    virtual void initRegistries() = 0;

    /**
     * @brief Initialize entities for the game scene.
     *
     * This function sets up the entities required for the game, adding them to the ECS registry.
     */
    virtual void initEntities() = 0;

    /**
     * @brief Initialize event for the game scene.
     *
     * This function sets up the events bind required for the game by the systems.
     */
    virtual void initEvents() = 0;

    /**
     * @brief Get the ECS registry associated with the game scene.
     *
     * @return GameEngine::ECS::Registry& Reference to the ECS registry.
     */
    virtual ECS::Registry& getEcsRegistry() = 0;

    /**
     * @brief Get the ECS registry ownership associated with the game scene.
     *
     * @return std::shared_ptr<Event::EventRegistry> Pointer to the ECS registry.
     */
    virtual std::shared_ptr<ECS::Registry> getSharedEcsRegistry() = 0;

    /**
     * @brief Get the Event registry associated with the game scene.
     *
     * @return GameEngine::Event::EventRegistry& Reference to the ECS registry.
     */
    virtual Event::EventRegistry& getEventRegistry() = 0;

    /**
     * @brief Get the Entity Factory associated with the game scene.
     *
     * @return GameEngine::ECS::Registry& Reference to the ECS registry.
     */
    virtual GameEngine::Entity::EntityFactory& getEntityFactory() = 0;

    virtual void onUpdate(size_t df) = 0;
  };
} // namespace GameEngine::Scene
