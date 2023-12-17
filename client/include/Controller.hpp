//
// Created by Alexandre Decobert on 16/12/2023.
//
#pragma once
#include <boost/asio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "ecs/Mediator.hpp"
#include "component/Gravity.hpp"
#include "component/Transform.hpp"
#include "system/Physics.hpp"
#include "network/Network.hpp"
#include <memory>

class Controller {
 public:
  Controller(std::shared_ptr<Mediator>& mediator);
  ~Controller() = default;
  void init(sf::RenderWindow& window);
  void setClientId(int id);
  int getClientId() const;
  void setRoomId(int id);
  int getRoomId() const;
  void setControllerId(int id);
  int getControllerId() const;

 private:
  void initPlayer(sf::RenderWindow& window);
  void initCRegister();
  void initSRegister();

  std::shared_ptr<Mediator> mediator;
  int id = 0;
  int controller_id = 0;
  int room_id = 0;
  std::vector<Entity> entities;
};
