//
// Created by raphael on 12/20/23.
//

#pragma once
#include "gameEngine/scene/SceneManager.hpp"
#include "graphics/GUI.hpp"
#include "network/Network.hpp"
#include <memory>
#include <string>

#define DEFAULT_RATIO (16.f / 9.f)

namespace Client {
class Client {
 public:
  Client();
  void initNetwork();
  void initGUI();
  void initScenes();
  void run();

 private:
  std::string appName = "Rtype client";
  std::unique_ptr<Network> m_network;
  std::unique_ptr<GUI> m_gui;
  //  std::unique_ptr<cLAAS> m_scenes;
};
}  // namespace Client
