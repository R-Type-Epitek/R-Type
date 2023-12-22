//
// Created by raphael on 12/20/23.
//

#include "gameEngine/scene/SceneContainer.hpp"
#include <stdexcept>

namespace GameEngine::Scene {
void SceneContainer::addScene(std::string const& name, std::unique_ptr<IScene> scene) {
  auto result = m_scenes.emplace(name, std::move(scene));
  if (!result.second) {
    throw std::invalid_argument("Scene with the same name:" + name + "already exists");
  }
};

void SceneContainer::deleteScene(std::string const& name) {
  if (!m_scenes.contains(name)) {
    throw std::invalid_argument("Scene with the name: " + name + " doesn't exists");
  }
  m_scenes.erase(name);
};

IScene& SceneContainer::getScene(std::string const& name) { return *m_scenes[name]; };

bool SceneContainer::exist(std::string const& name) { return m_scenes.contains(name); }

IScene& SceneContainer::find(std::string name) {
  auto it = m_scenes.find(name);
  if (it != m_scenes.end()) {
    return *(it->second);
  } else {
    throw std::out_of_range("Scene with the specified name not found");
  }
};

}  // namespace GameEngine::Scene
