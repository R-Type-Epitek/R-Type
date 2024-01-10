//
// Created by raphael on 12/20/23.
//

#pragma once
#include "gameEngine/core/Core.hpp"
#include "network/Network.hpp"

#include <memory>
#include <string>

namespace Client
{

  class Client {
   public:
    /**
     * @brief Construct a new Client object.
     */
    Client();

    void initNetwork();

    void initGameEngine();

    void initScenes();

    void run();

   private:
    std::string ip;
    std::string port;
    std::string appName;

    std::unique_ptr<GameEngine::Core::Core> m_coreGE;
    std::shared_ptr<Network> m_network;
  };
} // namespace Client
