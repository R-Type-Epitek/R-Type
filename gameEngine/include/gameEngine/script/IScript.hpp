//
// Created by raphael on 1/14/24.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/event/EventRegistry.hpp"
#include <memory>

namespace GameEngine::Script
{
  /**
   * @brief Interface for game scripts.
   */
  class IScript {
   public:
    /**
     * @brief Destructor.
     */
    virtual ~IScript() = default;

    /**
     * @brief Subscribe to relevant events.
     */
    virtual void subscribeEvent() = 0;

    /**
     * @brief If the script is configured.
     */
    virtual bool isConfigured() = 0;

    /**
     * @brief Update function called per frame.
     *
     * @param df The delta time in milliseconds.
     */
    virtual void execute(int df) = 0;

    /**
     * @brief Attach the script to an entity.
     *
     * @param entity The entity to attach the script.
     */
    virtual void attachEntity(const ECS::Entity entity) = 0;

    /**
     * @brief Attach the script to an ECS registry.
     *
     * @param ecsRegistry The ECS registry to attach.
     */
    virtual void attachEcsRegistry(std::shared_ptr<ECS::Registry> ecsRegistry) = 0;

    /**
     * @brief Attach the script to an event registry.
     *
     * @param eventRegistry The event registry to attach.
     */
    virtual void attachEventRegistry(std::shared_ptr<Event::EventRegistry> eventRegistry) = 0;
  };

} // namespace GameEngine::Script
