//
// Created by raphael on 1/10/24.
//

#include "gameEngine/core/Core.hpp"

#include "gameEngine/gfx/sfml/Renderer.hpp"
#include "gameEngine/scene/SceneManager.hpp"
#include <memory>
#include <chrono>
#include <thread>

namespace GameEngine::Core
{

  Core::Core()
    : m_projectName("Rtype")
    , m_ticksPerSecond(60)
    , m_gameEngineState(GameEngineState::LOADING)
    , m_graphical(false)
    , m_sceneManager(nullptr)
    , m_gui(nullptr)
  {
  }

  Core::Core(std::string projectName)
    : m_projectName(std::move(projectName))
    , m_ticksPerSecond(60)
    , m_gameEngineState(GameEngineState::LOADING)
    , m_graphical(false)
    , m_sceneManager(std::make_unique<GameEngine::Scene::SceneManager>())
    , m_gui(nullptr)
  {
  }

  void Core::run()
  {
    std::chrono::milliseconds tickDuration = std::chrono::milliseconds(1000 / m_ticksPerSecond);

    while (m_gameEngineState != GameEngineState::STOPPED) {
      auto startTime = std::chrono::steady_clock::now();

      if (m_graphical && !m_gui->isOpen()) {
        stop();
      }
      if (m_graphical) {
        m_gui->clear();
        m_gui->display();
      }
      m_sceneManager->getCurrent().onUpdate(1);

      auto endTime = std::chrono::steady_clock::now();
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
      auto sleepTime = tickDuration - elapsed;
      if (sleepTime > std::chrono::milliseconds(0)) {
        std::this_thread::sleep_for(sleepTime);
      }
    }
  }

  void Core::stop()
  {
    m_gameEngineState = GameEngineState::STOPPED;
  }

  void Core::loadPlugins()
  {
    m_sceneManager = std::make_unique<GameEngine::Scene::SceneManager>();
  }

  void Core::loadScenes()
  {
    m_sceneManager->initScenes();
  }

  void Core::addScene(const std::string& name, std::unique_ptr<Scene::IScene> scene)
  {
    m_sceneManager->addScene(name, std::move(scene));
  }

  void Core::setCurrentScene(const std::string& name)
  {
    return m_sceneManager->setCurrent(name);
  }

  void Core::enableGUI()
  {
    m_graphical = true;
    auto renderer = std::make_shared<Gfx::Sfml::Renderer>(1920, 1080, "GameEngine graphics");
    m_gui = std::make_unique<UI::Window>(renderer);
  }

  void Core::disableGUI()
  {
    m_graphical = false;
    m_gui.reset();
  }

  void Core::setTicksPerSecond(unsigned int ticksPerSecond)
  {
    m_ticksPerSecond = ticksPerSecond;
  }

  unsigned int Core::getTicksPerSecond() const
  {
    return m_ticksPerSecond;
  }
  const std::string& Core::getProjectName() const
  {
    return m_projectName;
  }

  const GameEngineState& Core::getGameEngineState() const
  {
    return m_gameEngineState;
  }

} // namespace GameEngine::Core