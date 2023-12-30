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
  class SceneContainer {
   public:
    SceneContainer() = default;

    void addScene(std::string const& name, std::unique_ptr<IScene> scene);
    void deleteScene(std::string const& name);
    IScene& getScene(std::string const& name);
    IScene& find(std::string const& name);

    typename std::map<std::string, std::unique_ptr<IScene>>::iterator begin()
    {
      return m_scenes.begin();
    }
    typename std::map<std::string, std::unique_ptr<IScene>>::iterator end()
    {
      return m_scenes.end();
    }

   private:
    bool exist(std::string const& name);
    std::map<std::string, std::unique_ptr<IScene>> m_scenes;
  };

} // namespace GameEngine::Scene
