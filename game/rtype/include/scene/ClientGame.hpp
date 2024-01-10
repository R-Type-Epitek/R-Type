//
// Created by raphael on 12/21/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/scene/SimpleScene.hpp"
#include "sceneController/GraphicController.hpp"

#include <memory>
#include <vector>

namespace Rtype::Scene
{
  class ClientGame : public GameEngine::Scene::SimpleScene {
   public:
    ClientGame(Controller::GraphicController &controller);

    void initRegistries() final;

    void initEntities() final;

    void initEvents() final;

    void onUpdate(size_t df) final;

   private:
    Controller::GraphicController m_controller;
  };
} // namespace Client
