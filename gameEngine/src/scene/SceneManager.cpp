//
// Created by raphael on 12/21/23.
//

#include "gameEngine/scene/SceneManager.hpp"

namespace GameEngine::Scene {

IScene& SceneManager::getCurrent() { return m_scenes.getScene(m_currentSceneName); }

void SceneManager::setCurrent(std::string name) { m_currentSceneName = name; }

}  // namespace GameEngine::Scene
