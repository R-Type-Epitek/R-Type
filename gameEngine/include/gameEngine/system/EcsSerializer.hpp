//
// Created by raphael on 12/24/23.
//

#pragma once

#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"

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
#include <functional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace GameEngine::System
{
  class EcsSerializer : public GameEngine::ECS::System {
    using Serializer = GameEngine::Network::Serializer::EcsSerializer;

  public:
    std::vector<std::vector<char>> serialise(GameEngine::ECS::Registry &registry)
    {
      auto &componentManager = registry.getComponentManager();
      std::vector<std::vector<char>> serializedDataFinal;

      for (auto const &entity : m_entities) {
        serializedDataFinal.push_back(serializeEntity(*componentManager, entity));
      }

      return serializedDataFinal;
    }

    void deserialize(
      GameEngine::ECS::Registry &registry,
      const std::vector<std::vector<char>> &serializedData)
    {
      auto &componentManager = registry.getComponentManager();

      for (const auto &serializedEntityData : serializedData) {
        deserializeEntity(registry, *componentManager, serializedEntityData);
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

      std::string dataStr = oss.str();
      serializedData.assign(dataStr.begin(), dataStr.end());
      return serializedData;
    }

    void deserializeEntity(
      GameEngine::ECS::Registry &registry,
      ECS::ComponentManager &componentManager,
      const std::vector<char> &serializedData)
    {
      std::istringstream iss(std::string(serializedData.begin(), serializedData.end()));
      boost::archive::binary_iarchive archive(iss);

      auto componentNE = Serializer::deserializeComponent<ComponentRType::NetworkedEntity>(archive);
      auto entity = getEntity(registry, componentManager, componentNE);

      Serializer::deserializeComponentToEntity<ComponentRType::MetaData>(componentManager, entity, archive);
    }

  private:
    ECS::Entity getEntity(
      GameEngine::ECS::Registry &registry,
      ECS::ComponentManager &componentManager,
      ComponentRType::NetworkedEntity componentId)
    {
      GameEngine::ECS::Entity entity = 0;
      auto entityOpt = getNetworkedEntityById(componentId, componentManager);

      if (entityOpt.has_value()) {
        entity = entityOpt.value();
      } else {
        entity = registry.createEntity();
        registry.addComponent(entity, std::move(componentId));
        registry.addComponent(entity, ComponentRType::MetaData {});
      }
      return entity;
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
