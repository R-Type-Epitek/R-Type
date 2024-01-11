//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/scene/IScene.hpp"
#include "gameEngine/scene/SimpleScene.hpp"
#include "sceneController/HostGameController.hpp"

#include <memory>
#include <vector>

namespace Rtype::Scene
{
  class HostGame : public GameEngine::Scene::SimpleScene {
   public:
    explicit HostGame(SceneController::HostGameController& controller);

    void initRegistries() final;

    void initEntities() final;

    void initEvents() final;

    void onUpdate(size_t df) final;

   private:
    SceneController::HostGameController m_controller;
  };
} // namespace Client
