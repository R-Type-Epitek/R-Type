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

    void addScene(SceneEnum name, std::unique_ptr<IScene> scene);
    void deleteScene(SceneEnum name);
    IScene& getScene(SceneEnum name);
    IScene& find(SceneEnum name);

    typename std::map<SceneEnum, std::unique_ptr<IScene>>::iterator begin()
    {
      return m_scenes.begin();
    }

    typename std::map<SceneEnum, std::unique_ptr<IScene>>::iterator end()
    {
      return m_scenes.end();
    }

   private:
    bool exist(SceneEnum name);
    std::map<SceneEnum, std::unique_ptr<IScene>> m_scenes;
  };

} // namespace GameEngine::Scene
