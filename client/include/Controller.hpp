//
// Created by Alexandre Decobert on 16/12/2023.
//
#pragma once
#include <boost/asio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "ecs/Mediator.hpp"

#include "network/Network.hpp"
#include <memory>

class Controller {
 public:
  Controller();
  ~Controller() = default;
  void setClientId(int id);
  int getClientId() const;
  void setRoomId(int id);
  int getRoomId() const;

 protected:
  int id = 0;
  int room_id = 0;std::vector<Entity> entities;
  std::shared_ptr<Mediator> mediator;

 private:
  void init();
  void initCRegister();
  void initSRegister();
};
