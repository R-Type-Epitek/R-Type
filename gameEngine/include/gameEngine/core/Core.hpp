//
// Created by raphael on 1/9/24.
//

#pragma once
#include <gameEngine/scene/ISceneManager.hpp>
#include <gameEngine/UI/Window.hpp>
#include <memory>

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
    Core() = default;
    ~Core() = default;

    void loadPlugins();

    void loadScenes();

    void run();

    void stop();

    //    - Scene -
    Scene::ISceneManager& getSceneManager();
    void initScenes();
    void addScene(const std::string& name, std::unique_ptr<Scene::IScene> scene);
    Scene::IScene& getCurrentScene();
    void setCurrentScene(const std::string& name);

    //    GUI
    void enableGUI();
    void disableGUI();

   private:
    unsigned int ticksPerSecond = 60;
    GameEngineState m_gameEngineState = GameEngineState::LOADING;
    bool m_graphicals = false;
    std::unique_ptr<Scene::ISceneManager> m_sceneManager;
    std::unique_ptr<UI::Window> m_gui;
  };

} // namespace GameEngine::Core
