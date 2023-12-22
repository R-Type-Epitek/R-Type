//
// Created by raphael on 12/21/23.
//

#include "scene/GameScene.hpp"

namespace Client {

GameScene::GameScene() {}

void GameScene::update() {}

GameEngine::ECS::Registry& GameScene::getECS() { return m_registry; }

}  // namespace Client
