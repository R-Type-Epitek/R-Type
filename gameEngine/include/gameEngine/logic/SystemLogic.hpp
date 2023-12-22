//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

namespace GameEngine::ECS {

class SystemLogic {
 public:
  SystemLogic() = default;
  ~SystemLogic() = default;

  void launchSystem(std::shared_ptr<Registry>& mediator, std::vector<Entity> entities, sf::RenderWindow& window);
};
}  // namespace GameEngine::ECS
