//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/scene/SceneManager.hpp"
#include "network/Network.hpp"

namespace Client::Scene
{
  /**
   * @brief Extended scene manager for the client-side application.
   *
   * SceneManager extends the game engine's scene manager functionality,
   * specializing it for client-side operations, including initializing scenes
   * with network capabilities.
   */
  class SceneManager : public GameEngine::Scene::SceneManager {
   public:
    /**
     * @brief Default destructor for SceneManager.
     */
    ~SceneManager() = default;

    /**
     * @brief Initialize the scenes for the client application.
     *
     * This function sets up the scenes required for the client side of the application,
     * utilizing the base scene manager functionality.
     */
    void initScenes() final;

    /**
     * @brief Initialize scenes with network integration.
     *
     * This function extends the basic scene initialization to include network
     * functionalities, allowing scenes to interact with network components.
     *
     * @param network Reference to the Network instance to be used in the scenes.
     */
    void initScenesWithNetwork(Network& network);
  };
} // namespace Client
