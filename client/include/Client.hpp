//
// Created by raphael on 12/20/23.
//

#pragma once
#include "gameEngine/UI/Window.hpp"
#include "graphics/GUI.hpp"
#include "network/Network.hpp"
#include "scene/SceneManager.hpp"

#include <memory>
#include <string>

namespace Client
{
  /**
   * @brief Main class for the client application.
   *
   * This class encompasses the core functionalities of the client application,
   * including network initialization, scene management, GUI setup, and the main
   * application loop.
   */
  class Client {
   public:
    /**
     * @brief Construct a new Client object.
     */
    Client();

    /**
     * @brief Initialize the network component of the client.
     */
    void initNetwork();

    /**
     * @brief Initialize the scene management component.
     */
    void initScenes();

    /**
     * @brief Initialize the Graphical User Interface (GUI).
     */
    void initGUI();

    /**
     * @brief Link different components of the application together.
     *
     * This function establishes connections and dependencies between various
     * components of the application, such as the network, scenes, and GUI.
     */
    void link();

    /**
     * @brief Run the main application loop.
     *
     * This function contains the primary loop of the application, where events
     * are processed, and updates and rendering are performed.
     */
    void run();

    /**
     * @brief Update the state of the application.
     *
     * @param ctx Reference to the WindowContext, containing relevant context information.
     */
    void update(GameEngine::UI::WindowContext &ctx);

    /**
     * @brief Handle events in the application.
     *
     * @param ctx Reference to the WindowContext, containing the event information.
     */
    void event(GameEngine::UI::WindowContext &ctx);

    /**
     * @brief Render the application's display.
     *
     * @param ctx Reference to the WindowContext, used for rendering elements on the screen.
     */
    void display(GameEngine::UI::WindowContext &ctx);

   private:
    std::string appName = "Rtype client";                ///< The name of the application.
    std::unique_ptr<Network> m_network;                  ///< Unique pointer to the network component.
    std::unique_ptr<GUI> m_gui;                          ///< Unique pointer to the GUI component.
    std::unique_ptr<Scene::SceneManager> m_sceneManager; ///< Unique pointer to the scene manager.
  };
} // namespace Client
