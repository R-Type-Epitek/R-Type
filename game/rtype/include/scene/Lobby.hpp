//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/scene/SimpleScene.hpp"
#include "sceneController/LobbyController.hpp"

#include <memory>
#include <vector>

namespace Rtype::Scene
{
  class Lobby : public GameEngine::Scene::SimpleScene {
   public:
    Lobby(SceneController::LobbyController &controller);

    void initRegistries() final;

    void initEntities() final;

    void initEvents() final;

    void onUpdate(size_t df) final;

   private:
    SceneController::LobbyController m_controller;
  };
} // namespace Client
