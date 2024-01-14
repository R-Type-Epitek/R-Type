//
// Created by raphael on 1/10/24.
//

#include "sceneController/GraphicController.hpp"

namespace Rtype::Controller
{
  GraphicController::GraphicController(
    std::shared_ptr<GameEngine::Gfx::IRenderer> renderer,
    std::shared_ptr<GameEngine::Network::INetworkController> network,
    std::shared_ptr<GameEngine::Scene::ISceneManager> sceneManager)
    : RendererController(std::move(renderer))
    , NetworkController(std::move(network))
    , SceneController(std::move(sceneManager))
  {
  }

  void GraphicController::initClassBinding()
  {
    addBinding("goToWelcomeScene", [this]() { this->goToWelcomeScene(); });
    addBinding("goToGameScene", [this]() { this->goToGameScene(); });
    addBinding("goToLobbyScene", [this]() { this->goToLobbyScene(); });
    addBinding("joinRoom0", [this]() { this->joinRoom(0); });
    addBinding("joinRoom1", [this]() { this->joinRoom(1); });
    addBinding("joinRoom2", [this]() { this->joinRoom(2); });
    addBinding("joinRoom3", [this]() { this->joinRoom(3); });
    addBinding("joinGame", [this]() { this->joinGame(); });
    addBinding("spectate", [this]() { this->spectate(); });
    addBinding("joinRoomAuto", [this]() { this->joinRoomAuto(); });
    addBinding("connect", [this]() { this->connect(); });
    addBinding("setName", [this]() { this->setName("Jhon Doe"); });
    addBinding("exitFast", [this]() { exit(0); });
  }

  void GraphicController::goToWelcomeScene()
  {
    getScenes().setCurrent("welcome");
  }

  void GraphicController::goToGameScene()
  {
    getScenes().setCurrent("game");
  }

  void GraphicController::goToLobbyScene()
  {
    getScenes().setCurrent("lobby");
  }

  void GraphicController::joinRoom(int id)
  {
    getNetwork().joinRoom(id);
  }

  void GraphicController::joinGame()
  {
    int id = getNetwork().getRoomId();

    if (id != -1) {
      getNetwork().joinGame(id);
      getScenes().setCurrent("game");
    }
  }

  void GraphicController::joinRoomAuto()
  {
    getNetwork().joinRoomAuto();
  }

  void GraphicController::spectate()
  {
    int id = getNetwork().getRoomId();

    if (id != -1) {
      getNetwork().spectate(id);
      getScenes().setCurrent("game");
    }
  }

  void GraphicController::connect()
  {
    getNetwork().connect();
  }

  void GraphicController::setName(std::string name)
  {
    getNetwork().updateName(name);
  }

} // namespace Rtype::Controller
