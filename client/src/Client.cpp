//
// Created by raphael on 12/20/23.
//

#include "Client.hpp"

#include "network/Constants.hpp"
#include "sceneController/GraphicController.hpp"
#include "scene/ClientGame.hpp"
#include "scene/SoloHostGame.hpp"
#include "scene/Lobby.hpp"
#include "scene/Welcome.hpp"
#include "network/Network.hpp"
#include "spdlog/spdlog.h"

#include <exception>
#include <memory>

namespace Client
{

  Client::Client()
    : ip(DEFAULT_IP)
    , port(DEFAULT_PORT)
    , appName("Rtype client")
  {
    spdlog::info("Starting Client...");
    initNetwork();
    initGameEngine();
    initScenes();
  };

  Client::Client(std::string const &ip, std::string const &port)
    : ip(ip)
    , port(port)
    , appName("Rtype client")
  {
    spdlog::info("Starting Client...");
    initNetwork();
    initGameEngine();
    initScenes();
  };

  void Client::initNetwork()
  {
    try {
      spdlog::info("Starting Network socket...");
      m_network = std::make_shared<Network>(DEFAULT_IP, DEFAULT_PORT);
      spdlog::info("Done");
    } catch (std::exception const &) {
      spdlog::error("Failed to initialize Network");
    }
  }

  void Client::initGameEngine()
  {
    spdlog::info("Starting Game Engine...");
    m_coreGE = std::make_unique<GameEngine::Core::Core>(appName);
    m_coreGE->loadPlugins();
    m_coreGE->enableGUI();
    m_coreGE->setTicksPerSecond(30);

    spdlog::info("Done");
  }

  void Client::initScenes()
  {
    auto controller = Rtype::Controller::GraphicController(
      m_coreGE->getGUI()->getSharedRenderer(),
      m_network,
      m_coreGE->getSceneManager());

    m_coreGE->addScene("game", std::make_unique<Rtype::Scene::ClientGame>(controller));
    m_coreGE->addScene("lobby", std::make_unique<Rtype::Scene::Lobby>(controller));
    m_coreGE->addScene("welcome", std::make_unique<Rtype::Scene::Welcome>(controller));
    m_coreGE->addScene("solo", std::make_unique<Rtype::Scene::SoloHostGame>(controller));

    m_coreGE->setCurrentScene("welcome");
    m_coreGE->loadScenes();
  }

  void Client::run()
  {
    m_coreGE->run();
  }

}; // namespace Client
