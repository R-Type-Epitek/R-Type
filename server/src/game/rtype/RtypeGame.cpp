//
// Created by raphael on 12/22/23.
//

#include "game/rtype/RtypeGame.hpp"
#include "gameEngine/system/EcsSerializer.hpp"
#include <vector>
#include <memory>

namespace Server::Game
{

  void RtypeGame::load()
  {
    m_scene.initRegistry();
    m_scene.initEntities();
  }

  std::vector<std::vector<char>> RtypeGame::getEntities()
  {
    auto& registry = m_scene.getECS();
    auto&& systems = registry.getSystems();
    std::vector<std::vector<char>> serializeData;

    for (auto& [typeId, system_ptr] : systems) {
      if (auto sys_serializer = std::dynamic_pointer_cast<GameEngine::System::EcsSerializer>(system_ptr)) {
        serializeData = sys_serializer->serialise(registry);
      }
    }
    return serializeData;
  }

} // namespace Server::Game