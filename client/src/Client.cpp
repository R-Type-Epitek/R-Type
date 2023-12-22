//
// Created by raphael on 12/20/23.
//

#include "Client.hpp"
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

void Client::update(GameEngine::UI::WindowContext&) { this->m_sceneManager.get(); }

void Client::event(GameEngine::UI::WindowContext&) { this->m_sceneManager.get(); }

void Client::display(GameEngine::UI::WindowContext&) { this->m_sceneManager.get(); }

void Client::testNetwork() {}

};  // namespace Client
