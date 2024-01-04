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
    auto compMetaData =
      ComponentRType::MetaData("assets/sprites/r-typesheet26.gif", GameEngine::Entity::EntityType::Enemy);
    factory.createFromNetwork(compId, compMetaData);
  }

  void RtypeGame::eventDisconnect(Player& player)
  {
    //    auto& registry = m_scene.getECS();
    //    auto&& entities = m_scene.getEntities();
    //
    //    for (auto& entity : entities) {
    //      if (!registry.hasComponent<ComponentRType::NetworkedEntity>(entity))
    //        continue;
    //      auto& comp = registry.getComponent<ComponentRType::NetworkedEntity>(entity);
    //      if (comp.id == player.id) {
    //        registry.destroyEntity(entity);
    //      }
    //    }
  }

  void RtypeGame::eventInput(Player& player)
  {
    auto& registry = m_scene.getECS();
    auto&& systems = registry.getSystems();

    for (auto& [typeId, system_ptr] : systems) {
      if (auto sys = std::dynamic_pointer_cast<GameEngine::System::Input>(system_ptr)) {
        sys->update(registry, player.id, player.key);
      }
      if (auto sysM = std::dynamic_pointer_cast<GameEngine::System::Move>(system_ptr)) {
        sysM->update(registry);
      }
    }
  };

} // namespace Server::Game