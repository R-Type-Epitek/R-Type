//
// Created by raphael on 1/9/24.
//

#pragma once
#include <gameEngine/scene/ISceneManager.hpp>
#include "gameEngine/scene/SceneManager.hpp"
#include <gameEngine/UI/Window.hpp>
#include <memory>
#include <utility>

namespace GameEngine::Core
{
  enum class GameEngineState
  {
    LOADING,
    RUNNING,
    STOPPED,
  };

  class Core {
   public:
    Core();

    Core(std::string projectName);

    ~Core() = default;

    void run();

    void stop();

    void loadPlugins();

    //    - Scene -
    void loadScenes();
    void addScene(const std::string& name, std::unique_ptr<Scene::IScene> scene);
    void setCurrentScene(const std::string& name);

    //    GUI
    void enableGUI();
    void disableGUI();

    //    - Tick rate -
    void setTicksPerSecond(unsigned int ticksPerSecond);
    unsigned int getTicksPerSecond() const;

    //    - Getters -
    const std::string& getProjectName() const;
    const GameEngineState& getGameEngineState() const;

   private:
    const std::string m_projectName;
    unsigned int m_ticksPerSecond;
    GameEngineState m_gameEngineState;
    bool m_graphical;

    std::unique_ptr<Scene::ISceneManager> m_sceneManager;
    std::unique_ptr<UI::Window> m_gui;
  };

} // namespace GameEngine::Core
