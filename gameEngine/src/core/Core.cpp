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
    unsigned int rateDelta = 0;

    while (m_gameEngineState != GameEngineState::STOPPED) {
      rateDelta++;
      auto startTime = std::chrono::steady_clock::now();
      auto deltaTime =
        std::chrono::duration_cast<std::chrono::duration<float>>(startTime - m_lastFrameTime).count();
      m_lastFrameTime = startTime;

      tickUpdate(deltaTime);
      if (m_updateExternClosure && rateDelta >= m_updateClosureRate) {
        m_updateExternClosure();
        rateDelta = 0;
      }
      auto endTime = std::chrono::steady_clock::now();
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
      auto sleepTime = tickDuration - elapsed;
      if (sleepTime > std::chrono::milliseconds(0)) {
        std::this_thread::sleep_for(sleepTime);
      }
    }
  }

  void Core::tickUpdate(unsigned int df)
  {
    if (m_graphical && !m_gui->isOpen()) {
      stop();
    }
    if (m_graphical) {
      m_gui->display();
    }
    m_sceneManager->getCurrent().onUpdate(df);
  }

  void Core::assignUpdateClosure(const std::function<void()>& closure, unsigned int updateRate)
  {
    m_updateExternClosure = closure;
    m_updateClosureRate = updateRate;
  }

  void Core::stop()
  {
    m_gameEngineState = GameEngineState::STOPPED;
  }

  void Core::loadPlugins()
  {
    m_sceneManager = std::make_shared<GameEngine::Scene::SceneManager>();
  }

  void Core::loadScenes()
  {
    m_sceneManager->initScenes();
  }

  void Core::addScene(const std::string& name, std::unique_ptr<Scene::IScene> scene)
  {
    m_sceneManager->addScene(name, std::move(scene));
  }

  Scene::IScene& Core::getCurrentScene()
  {
    return m_sceneManager->getCurrent();
  }

  void Core::setCurrentScene(const std::string& name)
  {
    return m_sceneManager->setCurrent(name);
  }

  void Core::enableGUI()
  {
    m_graphical = true;
    m_gui =
      std::make_shared<UI::Window>(std::make_shared<Gfx::Sfml::Renderer>(1920, 1080, "GameEngine graphics"));
    m_gui->setFramerateLimit(60);
  }

  void Core::disableGUI()
  {
    m_graphical = false;
    m_gui.reset();
  }

  std::shared_ptr<UI::Window> Core::getGUI()
  {
    return m_gui;
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