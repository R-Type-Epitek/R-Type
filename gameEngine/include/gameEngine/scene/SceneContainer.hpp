//
// Created by raphael on 12/20/23.
//

#pragma once

#include "IScene.hpp"

#include <map>
#include <memory>
#include <string>

namespace GameEngine::Scene
{
  template<typename SceneEnum>
  class SceneContainer {
   public:
    SceneContainer() = default;

    void addScene(SceneEnum name, std::unique_ptr<IScene> scene)
    {
      auto result = m_scenes.emplace(name, std::move(scene));
      if (!result.second) {
        throw std::invalid_argument("Scene with the same name already exists");
      }
    };

    void deleteScene(SceneEnum name)
    {
      if (!m_scenes.contains(name)) {
        throw std::invalid_argument("Scene with the name doesn't exists");
      }
      m_scenes.erase(name);
    };
    IScene& getScene(SceneEnum name)
    {
      return *m_scenes[name];
    };

    IScene& find(SceneEnum name)
    {
      auto it = m_scenes.find(name);
      if (it != m_scenes.end()) {
        return *(it->second);
      } else {
        std::string msg = "Scene with the specified name not found";
        throw std::out_of_range(msg);
      }
    };

    typename std::map<SceneEnum, std::unique_ptr<IScene>>::iterator begin()
    {
      return m_scenes.begin();
    }

    typename std::map<SceneEnum, std::unique_ptr<IScene>>::iterator end()
    {
      return m_scenes.end();
    }

   private:
    bool exist(SceneEnum name)
    {
      return m_scenes.contains(name);
    }
    std::map<SceneEnum, std::unique_ptr<IScene>> m_scenes;
  };

} // namespace GameEngine::Scene
