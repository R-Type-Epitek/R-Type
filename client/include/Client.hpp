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

#define DEFAULT_RATIO (16.f / 9.f)

namespace Client
{
  class Client {
  public:
    Client();
    void initNetwork();
    void initScenes();
    void initGUI();
    void link();
    void run();

    void testNetwork();

    //  Closure
    void update(GameEngine::UI::WindowContext &);
    void event(GameEngine::UI::WindowContext &);
    void display(GameEngine::UI::WindowContext &);

  private:
    std::string appName = "Rtype client";
    std::unique_ptr<Network> m_network;
    std::unique_ptr<GUI> m_gui;
    std::unique_ptr<SceneManager> m_sceneManager;
  };
} // namespace Client
