//
// Created by raphael on 12/20/23.
//

#include "Client.hpp"
#include "spdlog/spdlog.h"

namespace Client {

Client::Client() { spdlog::info("Starting Client..."); };

void Client::initNetwork() {
  spdlog::info("Starting Network...");
  try {
    m_network = std::make_unique<Network>(DEFAULT_IP, DEFAULT_PORT);
  } catch (std::exception) {
    spdlog::error("Failed to initialize Network");
  }
}

void Client::initGUI() {
  spdlog::info("Starting GUI...");
  try {
    m_gui = std::make_unique<GUI>(1920, 1080, appName, DEFAULT_RATIO);
  } catch (std::exception) {
    spdlog::error("Failed to initialize GUI");
  }
}

void Client::initScenes() {
  spdlog::info("Starting Scenes...");
  try {
    m_gui = std::make_unique<GUI>(1920, 1080, appName, DEFAULT_RATIO);
  } catch (std::exception) {
    spdlog::error("Failed to initialize Scenes");
  }
}

void Client::run() { m_gui->launch(); }

};  // namespace Client
