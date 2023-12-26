//
// Created by raphael on 12/21/23.
//

#pragma once
#include "RTypeClient.hpp"

namespace Client
{
  class SceneManager : public GameEngine::Scene::SceneManager {
  public:
    ~SceneManager() = default;

    void initScenes() final;
    void initScenesWithNetwork(Network& network);
  };

} // namespace Client
