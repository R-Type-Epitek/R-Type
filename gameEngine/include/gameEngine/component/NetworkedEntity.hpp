//
// Created by raphael on 12/28/23.
//

#pragma once
#include "gameEngine/network/Serializer.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"

#include <boost/serialization/base_object.hpp>
#include <cstddef>

namespace ComponentRType
{

  struct NetworkedEntity : public GameEngine::Network::Serializer::BaseNetworkComponent {
    size_t id;

    NetworkedEntity() = default;
    explicit NetworkedEntity(size_t id)
      : id(id)
    {
    }

    friend bool operator==(const NetworkedEntity &lhs, const NetworkedEntity &rhs)
    {
      return lhs.id == rhs.id;
    }

    static GameEngine::ECS::Entity getEntityByNetworkedId(
      const size_t &id,
      const std::set<GameEngine::ECS::Entity> &entities,
      GameEngine::ECS::ComponentManager &componentManager)
    {
      auto it = std::find_if(
        entities.begin(),
        entities.end(),
        [&componentManager, id](const GameEngine::ECS::Entity &entity) {
          auto currentId = componentManager.getComponent<ComponentRType::NetworkedEntity>(entity);
          return id == currentId.id;
        });
      if (it != entities.end()) {
        return *it;
      } else {
        throw std::out_of_range("Entity not found with the specified ID");
      }
    }

   private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &archive, const unsigned int)
    {
      archive &boost::serialization::base_object<GameEngine::Network::Serializer::BaseNetworkComponent>(
        *this);
      archive & id;
    }
  };

} // namespace ComponentRType
