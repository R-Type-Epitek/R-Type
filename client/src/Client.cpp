//
// Created by raphael on 12/20/23.
//

#include "Client.hpp"
#define DEFAULT_RATIO (16.f / 9.f)

namespace Client {

Client::Client() = default;
void Client::initNetwork() { m_network = std::make_unique<Network>(DEFAULT_IP, DEFAULT_PORT); }

void Client::initGUI() { m_gui = std::make_unique<GUI>(1920, 1080, appName, DEFAULT_RATIO); }

void Client::initScenes() {}

void Client::run() { m_gui->launch(); }

};  // namespace Client
