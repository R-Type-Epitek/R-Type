//
// Created by raphael on 1/10/24.
//

#pragma once
#include "RendererController.hpp"
#include "NetworkController.hpp"
#include "BindingController.hpp"
#include "SceneController.hpp"

namespace Rtype::Controller
{
  class GraphicController
    : public RendererController
    , public NetworkController
    , public SceneController
    , public BindingController {
   public:
    explicit GraphicController(
      std::shared_ptr<GameEngine::Gfx::IRenderer> renderer,
      std::shared_ptr<GameEngine::Network::INetworkController> network,
      std::shared_ptr<GameEngine::Scene::ISceneManager> sceneManager);

    ~GraphicController() = default;

    void initClassBinding() final;

    //    Scene
    void goToWelcomeScene();
    void goToGameScene();
    void goToLobbyScene();

    //    Network
    void joinRoom(int id);
    void joinGame();
    void joinRoomAuto();
    void spectate();
    void connect();
    void setName(std::string name);
  };
} // namespace Rtype::GraphicController
