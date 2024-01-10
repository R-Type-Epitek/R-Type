//
// Created by raphael on 1/10/24.
//

#include "gameEngine/core/Core.hpp"

#include "gameEngine/gfx/sfml/Renderer.hpp"
#include <memory>
#include <chrono>
#include <thread>

namespace GameEngine::Core
{

  void Core::loadPlugins()
  {
  }

  void Core::loadScenes()
  {
  }

  void Core::run()
  {
    std::chrono::milliseconds tickDuration = std::chrono::milliseconds(1000 / ticksPerSecond);

    while (m_gameEngineState != GameEngineState::STOPPED) {
      auto startTime = std::chrono::steady_clock::now();

      if (m_graphicals && !m_gui->isOpen()) {
        m_gameEngineState = GameEngineState::STOPPED;
      }
      if (m_graphicals) {
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
  }

  Scene::ISceneManager& Core::getSceneManager()
  {
    return *m_sceneManager;
  }

  void Core::initScenes()
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
    m_graphicals = true;
    auto renderer = std::make_shared<Gfx::Sfml::Renderer>(1920, 1080, "GameEngine graphics");
    m_gui = std::make_unique<UI::Window>(renderer);
  }

  void Core::disableGUI()
  {
    m_graphicals = false;
    m_gui.reset();
  }

} // namespace GameEngine::Core