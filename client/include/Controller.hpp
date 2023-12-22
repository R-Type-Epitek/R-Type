//
// Created by Alexandre Decobert on 16/12/2023.
//
#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include <memory>
#include <vector>

class Controller {
 public:
  Controller();
  ~Controller() = default;
  void setClientId(int identifier);
  int getClientId() const;
  void setRoomId(int identifier);
  int getRoomId() const;

 protected:
  std::vector<GameEngine::ECS::Entity> entities;
  std::shared_ptr<GameEngine::ECS::Registry> registry;

 private:
  void init();
  void initCRegister();
  void initSRegister();

  int id = 0;
  int room_id = 0;
};
