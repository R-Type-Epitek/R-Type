//
// Created by raphael on 12/21/23.
//

#include "scene/GameScene.hpp"

namespace Client {

GameScene::GameScene() { m_registry.init(); }

void GameScene::update() {}

Registry& GameScene::getECS() { return m_registry; }

}  // namespace Client
