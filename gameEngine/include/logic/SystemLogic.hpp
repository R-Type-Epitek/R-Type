//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once
#include "ecs/entity/Entity.hpp"
#include "ecs/Mediator.hpp"
#include "ecs/Signature.hpp"
#include <memory>

class SystemLogic {
 public:
  SystemLogic() = default;
  ~SystemLogic() = default;

  void launchSystem(std::shared_ptr<Mediator>& mediator, std::vector<Entity> entities, sf::RenderWindow& window);
};