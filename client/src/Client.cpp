//
// Created by raphael on 12/20/23.
//

#include "Client.hpp"

#include "gameEngine/UI/Window.hpp"
#include "gameEngine/system/Animation.hpp"
#include "gameEngine/system/EcsSerializer.hpp"
#include "gameEngine/system/IUpdateSystem.hpp"
#include "gameEngine/system/Keyboard.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "gameEngine/system/Move.hpp"
#include "graphics/GUI.hpp"
#include "network/Constants.hpp"
#include "network/Network.hpp"
#include "network/system/Keyboard.hpp"
#include "scene/SceneManager.hpp"
#include "spdlog/spdlog.h"

#include <exception>
#include <memory>

namespace Client
{

  Client::Client()
  {
    spdlog::info("Starting Client...");
  };

  void Client::initNetwork()
  {
    try {
      spdlog::info("Starting Network...");
      m_network = std::make_unique<Network>(DEFAULT_IP, DEFAULT_PORT);
      spdlog::info("Done");

      spdlog::info("Establishing Network connection...");
      m_network->connectToServer();
      spdlog::info("Done");

      spdlog::info("Getting Server id...");
      while (m_network->getClientId() == -1) {
      };
      spdlog::info("Done");

      spdlog::info("Connecting to game room [0]...");
      m_network->updateName("John Doe");
      m_network->joinRoom(0);
      m_network->joinGame(0);
      spdlog::info("Done");

    } catch (std::exception const&) {
      spdlog::error("Failed to initialize Network");
    }
  }

  void Client::initScenes()
  {
    try {
      spdlog::info("Starting Scenes...");
      m_sceneManager = std::make_unique<Scene::SceneManager>();
      m_sceneManager->initScenes();
      m_sceneManager->initScenesWithNetwork(*m_network);
      spdlog::info("Done");
    } catch (std::exception const&) {
      spdlog::error("Failed to initialize Scenes");
    }
  }

  void Client::initGUI()
  {
    try {
      spdlog::info("Starting GUI...");
      m_gui = std::make_unique<GUI>(1920, 1080, appName, DEFAULT_RATIO);
      spdlog::info("Done");
    } catch (std::exception const&) {
      spdlog::error("Failed to initialize GUI");
    }
  }

  void Client::link()
  {
    spdlog::info("Linking Everything to GUI...");
    m_gui->setFrameRate(60);
    m_gui->subscribeUpdate([this](GameEngine::UI::WindowContext& ctx) {
      this->update(ctx);
    });
    m_gui->subscribeEvent([this](GameEngine::UI::WindowContext& ctx) {
      this->event(ctx);
    });
    m_gui->subscribeDisplay([this](GameEngine::UI::WindowContext& ctx) {
      this->display(ctx);
    });
    spdlog::info("Done");
  };

  void Client::run()
  {
    m_gui->launch();
  }

  void Client::update(GameEngine::UI::WindowContext& ctx)
  {
    auto& registry = this->m_sceneManager->getCurrent().getEcsRegistry();

    try {
      {
        auto system = registry.getSystem<GameEngine::System::Animation>();
        system->update(registry, ctx);
      }
      {
        auto system = registry.getSystem<GameEngine::System::Move>();
        system->updateClient(registry);
      }
      {
        auto sys_serializer = registry.getSystem<GameEngine::System::EcsSerializer>();
        auto& queue = m_network->getSerializedEcsQueue();
        auto& factory = this->m_sceneManager->getCurrent().getEntityFactory();

        sys_serializer->deserialize(registry, queue, factory);
      }

    } catch (const std::exception& e) {
      spdlog::error("[Client update] Error: {}", e.what());
    }
  }

  void Client::event(GameEngine::UI::WindowContext& ctx)
  {
    auto& registry = this->m_sceneManager->getCurrent().getEcsRegistry();

    try {
      auto system = registry.getSystem<System::Network::Keyboard>();
      system->update(ctx, *m_network);

    } catch (const std::exception& e) {
      spdlog::error("[Client Event] Error: {}", e.what());
    }
  }

  void Client::display(GameEngine::UI::WindowContext& ctx)
  {
    auto& registry = this->m_sceneManager->getCurrent().getEcsRegistry();

    try {
      {
        auto system = registry.getSystem<GameEngine::System::Renderer>();
        system->update(registry, ctx);
      }
    } catch (const std::exception& e) {
      spdlog::error("[Client display] Error: {}", e.what());
    }
  }
}; // namespace Client
