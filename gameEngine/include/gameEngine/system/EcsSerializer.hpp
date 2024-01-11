//
// Created by raphael on 12/24/23.
//

#pragma once

#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Transform.hpp"

#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/network/Serializer.hpp"

#include <algorithm>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace GameEngine::System
{
  class EcsSerializer
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder {
    using Serializer = GameEngine::Network::Serializer::EcsSerializer;

   public:
    std::vector<std::vector<char>> serialise()
    {
      auto &componentManager = getEcsRegistry().getComponentManager();
      std::vector<std::vector<char>> serializedDataFinal;

      for (auto const &entity : m_entities) {
        serializedDataFinal.push_back(serializeEntity(*componentManager, entity));
      }
      return serializedDataFinal;
    }

    void deserialize(
      const std::vector<std::vector<char>> &serializedData,
      GameEngine::Entity::EntityFactory &entityFactory)
    {
      auto &componentManager = getEcsRegistry().getComponentManager();

      for (const auto &serializedEntityData : serializedData) {
        deserializeEntity(*componentManager, serializedEntityData, entityFactory);
      }
    }

   protected:
    static std::vector<char> serializeEntity(
      ECS::ComponentManager &componentManager,
      GameEngine::ECS::Entity entity)
    {
      std::vector<char> serializedData;
      std::ostringstream oss;
      boost::archive::binary_oarchive archive(oss);

      Serializer::serializeComponent<ComponentRType::NetworkedEntity>(componentManager, entity, archive);
      Serializer::serializeComponent<ComponentRType::MetaData>(componentManager, entity, archive);
      Serializer::serializeComponent<ComponentRType::Position>(componentManager, entity, archive);
      Serializer::serializeComponent<ComponentRType::Transform>(componentManager, entity, archive);

      std::string dataStr = oss.str();
      serializedData.assign(dataStr.begin(), dataStr.end());
      return serializedData;
    }

    void deserializeEntity(
      ECS::ComponentManager &componentManager,
      const std::vector<char> &serializedData,
      GameEngine::Entity::EntityFactory &entityFactory)
    {
      GameEngine::ECS::Entity entity = 0;
      std::istringstream iss(std::string(serializedData.begin(), serializedData.end()));
      boost::archive::binary_iarchive archive(iss);

      auto componentNE = Serializer::deserializeComponent<ComponentRType::NetworkedEntity>(archive);
      auto componentMD = Serializer::deserializeComponent<ComponentRType::MetaData>(archive);

      auto entityOpt = getNetworkedEntityById(componentNE, componentManager);
      if (entityOpt.has_value()) {
        entity = entityOpt.value();
      } else {
        entity = entityFactory.createFromNetwork(componentNE, componentMD);
      }
      return updateEntity(componentManager, entity, archive);
    }

   private:
    void updateEntity(
      GameEngine::ECS::ComponentManager &componentManager,
      const GameEngine::ECS::Entity &entity,
      boost::archive::binary_iarchive &archive)
    {
      Serializer::deserializeComponentToEntity<ComponentRType::Position>(componentManager, entity, archive);
      Serializer::deserializeComponentToEntity<ComponentRType::Transform>(componentManager, entity, archive);
    }

    std::optional<const ECS::Entity> getNetworkedEntityById(
      ComponentRType::NetworkedEntity id,
      ECS::ComponentManager &componentManager)
    {
      auto it = std::find_if(
        m_entities.begin(),
        m_entities.end(),
        [&componentManager, &id](const GameEngine::ECS::Entity &entity) {
          auto currentId = componentManager.getComponent<ComponentRType::NetworkedEntity>(entity);
          return id == currentId;
        });

      static std::optional<const GameEngine::ECS::Entity> emptyOptional;
      return (it != m_entities.end()) ? std::ref(*it) : emptyOptional;
    }
  };
}; // namespace GameEngine::System
