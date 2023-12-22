//
// Created by raphael on 12/20/23.
//

#include "Client.hpp"
#include "gameEngine/UI/Window.hpp"
#include "gameEngine/system/Animation.hpp"
#include "gameEngine/system/Keyboard.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "graphics/GUI.hpp"
#include "network/Network.hpp"
#include "scene/SceneManager.hpp"
#include "spdlog/spdlog.h"
#include <exception>
#include <memory>

namespace Client {

Client::Client() { spdlog::info("Starting Client..."); };

void Client::initNetwork() {
  spdlog::info("Starting Network...");
  try {
    m_network = std::make_unique<Network>(DEFAULT_IP, DEFAULT_PORT);
  } catch (std::exception const&) {
    spdlog::error("Failed to initialize Network");
  }
}

void Client::initGUI() {
  spdlog::info("Starting GUI...");
  try {
    m_gui = std::make_unique<GUI>(1920, 1080, appName, DEFAULT_RATIO);
  } catch (std::exception const&) {
    spdlog::error("Failed to initialize GUI");
  }
}

void Client::initScenes() {
  spdlog::info("Starting Scenes...");
  try {
    m_sceneManager = std::make_unique<SceneManager>();
    m_sceneManager->initScenes();

  } catch (std::exception const&) {
    spdlog::error("Failed to initialize Scenes");
  }
}

void Client::link() {
  m_gui->subscribeUpdate([this](GameEngine::UI::WindowContext& ctx) { this->update(ctx); });
  m_gui->subscribeEvent([this](GameEngine::UI::WindowContext& ctx) { this->event(ctx); });
  m_gui->subscribeDisplay([this](GameEngine::UI::WindowContext& ctx) { this->display(ctx); });
};

void Client::run() { m_gui->launch(); }

void Client::update(GameEngine::UI::WindowContext& ctx) {
  auto& ecs = this->m_sceneManager->getCurrent().getECS();
  auto&& systems = ecs.getSystems();

  for (auto& [typeId, system_ptr] : systems) {
    if (auto sys_physics = std::dynamic_pointer_cast<GameEngine::System::Physics>(system_ptr)) {
      sys_physics->update();
    } else if (auto sys_renderer = std::dynamic_pointer_cast<GameEngine::System::Renderer>(system_ptr)) {
      sys_renderer->update(ecs, ctx);
    } else if (auto sys_animation = std::dynamic_pointer_cast<GameEngine::System::Animation>(system_ptr)) {
      sys_animation->update(ecs);
    }
  }
}

void Client::event(GameEngine::UI::WindowContext& ctx) {
  auto& ecs = this->m_sceneManager->getCurrent().getECS();
  auto&& systems = ecs.getSystems();

  for (auto& [typeId, system_ptr] : systems) {
    if (auto sys_keyboard = std::dynamic_pointer_cast<GameEngine::System::Keyboard>(system_ptr)) {
      sys_keyboard->update(ecs, ctx);
    }
  }
}

void Client::display(GameEngine::UI::WindowContext&) { return; }

void Client::testNetwork() {}

};  // namespace Client
