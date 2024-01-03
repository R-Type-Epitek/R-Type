//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/scene/IScene.hpp"
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
  class GameScene : public GameEngine::Scene::IScene {
   public:
    /**
     * @brief Construct a new GameScene object.
     *
     * @param network Reference to the Network instance used for network interactions.
     */
    GameScene(Network& network);

    /**
     * @brief Initialize the ECS registry for the game scene.
     */
    void initRegistry() final;

    /**
     * @brief Initialize entities for the game scene.
     *
     * This function sets up the entities required for the game, adding them to the ECS registry.
     */
    void initEntities() final;

    /**
     * @brief Get the ECS registry associated with the game scene.
     *
     * @return GameEngine::ECS::Registry& Reference to the ECS registry.
     */
    GameEngine::ECS::Registry& getECS() final;

    std::vector<GameEngine::ECS::Entity>& getEntities() final;

   protected:
    /**
     * @brief Initialize custom systems specific to this game scene.
     *
     * This method is used to set up any custom systems that are specific to the game scene,
     * such as rendering or physics systems.
     */
    void initCustomSystem();

   private:
    std::vector<GameEngine::ECS::Entity> m_entities;       ///< Vector of entities in the game scene.
    std::unique_ptr<GameEngine::ECS::Registry> m_registry; ///< Unique pointer to the ECS registry.
    Network& m_network; ///< Reference to the network instance for network interactions.
  };
} // namespace Client
