//
// Created by raphael on 12/20/23.
//

#include "Client.hpp"

#include "gameEngine/UI/Window.hpp"
#include "gameEngine/system/Animation.hpp"
#include "gameEngine/system/EcsSerializer.hpp"
#include "gameEngine/system/Keyboard.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/Renderer.hpp"
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

  void Client::update(GameEngine::UI::WindowContext&)
  {
    auto& ecs = this->m_sceneManager->getCurrent().getECS();
    auto&& systems = ecs.getSystems();

    for (auto& [typeId, system_ptr] : systems) {
      if (auto sys_physics = std::dynamic_pointer_cast<GameEngine::System::Physics>(system_ptr)) {
        sys_physics->update();
      } else if (
        auto sys_serializer = std::dynamic_pointer_cast<GameEngine::System::EcsSerializer>(system_ptr)) {
        auto& queue = m_network->getSerializedEcsQueue();
        auto& entities = this->m_sceneManager->getCurrent().getEntities();

        sys_serializer->deserialize(ecs, entities, queue);
      }
    }
  }

  void Client::event(GameEngine::UI::WindowContext& ctx)
  {
    auto& ecs = this->m_sceneManager->getCurrent().getECS();
    auto&& systems = ecs.getSystems();

    for (auto& [typeId, system_ptr] : systems) {
      if (auto sys_keyboard = std::dynamic_pointer_cast<GameEngine::System::Keyboard>(system_ptr)) {
        sys_keyboard->update(ecs, ctx);
      }
      if (auto sys_keyboard_net = std::dynamic_pointer_cast<System::Network::Keyboard>(system_ptr)) {
        sys_keyboard_net->update(ctx, *m_network);
      }
    }
  }

  void Client::display(GameEngine::UI::WindowContext& ctx)
  {
    auto& ecs = this->m_sceneManager->getCurrent().getECS();
    auto&& systems = ecs.getSystems();

    for (auto& [typeId, system_ptr] : systems) {
      if (auto sys_renderer = std::dynamic_pointer_cast<GameEngine::System::Renderer>(system_ptr)) {
        sys_renderer->update(ecs, ctx);
      } else if (auto sys_animation = std::dynamic_pointer_cast<GameEngine::System::Animation>(system_ptr)) {
        sys_animation->update(ecs);
      }
    }
  }
}; // namespace Client
