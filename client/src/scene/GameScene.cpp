//
// Created by raphael on 12/21/23.
//

#include "scene/GameScene.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "spdlog/spdlog.h"

namespace Client {

GameScene::GameScene() {}

void GameScene::update() {}

GameEngine::ECS::Registry& GameScene::getECS() { return m_ecsController.getECS(); }

}  // namespace Client
