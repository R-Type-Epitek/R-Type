//
// Created by raphael on 12/21/23.
//

#include "gameEngine/scene/SceneManager.hpp"
#include <cassert>

namespace GameEngine::Scene {

IScene& SceneManager::getCurrent() { return m_scenes.find(m_currentSceneName); }

void SceneManager::setCurrent(std::string name) { m_currentSceneName = name; }

}  // namespace GameEngine::Scene
