//
// Created by Alexandre Decobert on 16/12/2023.
//
#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include <memory>
#include <vector>

namespace Client::ECS {
class EcsGameController {
 public:
  friend class GameScene;

  EcsGameController();
  ~EcsGameController() = default;
  void setClientId(int identifier);
  int getClientId() const;
  void setRoomId(int identifier);
  int getRoomId() const;
  GameEngine::ECS::Registry& getECS();

 private:
  void init();
  void initCRegister();
  void initSRegister();

  std::vector<GameEngine::ECS::Entity> m_entities;
  GameEngine::ECS::Registry m_registry;
  int m_id = 0;
  int m_roomId = 0;
};
}  // namespace Client::ECS
