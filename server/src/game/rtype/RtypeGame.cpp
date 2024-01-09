//
// Created by raphael on 12/22/23.
//

#include "game/rtype/RtypeGame.hpp"
#include "gameEngine/system/EcsSerializer.hpp"
#include "gameEngine/system/Keyboard.hpp"
#include "gameEngine/system/Input.hpp"
#include "gameEngine/system/Move.hpp"
#include <vector>
#include <memory>

namespace Server::Game
{

  void RtypeGame::load()
  {
    m_scene.initRegistries();
    m_scene.initEntities();
  }

  std::vector<std::vector<char>> RtypeGame::getEntities()
  {
    auto& registry = m_scene.getEcsRegistry();

    auto system = registry.getSystem<GameEngine::System::EcsSerializer>();
    return system->serialise(registry);
  }

  void RtypeGame::pushEvent(Event event, Player player)
  {
    switch (event) {
      case Event::Connect:
        eventConnect(player);
        break;
      case Event::Disconnect:
        eventDisconnect(player);
        break;
      case Event::Input:
        eventInput(player);
        break;
    }
  }

  void RtypeGame::eventConnect(Player& player)
  {
    auto factory = m_scene.getEntityFactory();
    auto compId = ComponentRType::NetworkedEntity {player.id};
    auto compMetaData = ComponentRType::MetaData("assets/sprites/r-typesheet26.gif", GameEngine::Entity::EntityType::Player);
    factory.createFromNetwork(compId, compMetaData);
  }

  void RtypeGame::eventDisconnect(Player& player)
  {
    auto& registry = m_scene.getEcsRegistry();
    auto&& entities = m_scene.getEntities();

    for (auto& entity : entities) {
      if (!registry.hasComponent<ComponentRType::NetworkedEntity>(entity))
        continue;
      auto& comp = registry.getComponent<ComponentRType::NetworkedEntity>(entity);
      if (comp.id == player.id) {
        registry.destroyEntity(entity);
      }
    }
  }

  void RtypeGame::eventInput(Player& player)
  {
    auto& registry = m_scene.getEcsRegistry();
    auto&& systems = registry.getSystems();

    try {
      {
        auto system = registry.getSystem<GameEngine::System::Input>();
        system->update(registry, player.id, player.key);
      }
      {
        auto system = registry.getSystem<GameEngine::System::Move>();
        system->update(registry);
      }
    } catch (const std::exception& e) {
      spdlog::error(e.what());
    }
  };

} // namespace Server::Game