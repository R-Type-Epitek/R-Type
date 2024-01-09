//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/scene/SceneManager.hpp"
#include "network/Network.hpp"

namespace Client::Scene
{

  enum class SceneType
  {
    Welcome,
    Lobby,
    Game,
  };

  class SceneManager : public GameEngine::Scene::SceneManager<SceneType> {
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
