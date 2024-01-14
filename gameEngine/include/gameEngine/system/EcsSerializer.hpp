//
// Created by raphael on 12/24/23.
//

#pragma once

#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/asset/AssetManager.hpp"

#include "gameEngine/entity/EntityFactory.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/network/Serializer.hpp"
#include "spdlog/spdlog.h"

#include <algorithm>
#include <boost/archive/archive_exception.hpp>
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
    : public ECS::System
    , public ECS::RegistryHolder {
    using Serializer = Network::Serializer::EcsSerializer;

   public:
    std::vector<std::vector<char>> serialise()
    {
      auto &componentManager = getEcsRegistry().getComponentManager();
      std::vector<std::vector<char>> serializedDataFinal;
      try {
        for (auto const &entity : m_entities) {
          serializedDataFinal.push_back(serializeEntity(*componentManager, entity));
        }

      } catch (const boost::archive::archive_exception &e) {
        spdlog::error("Caught boost::archive::archive_exception: {}", e.what());
      }
      return serializedDataFinal;
    }

    void deserialize(
      const std::vector<std::vector<char>> &serializedData,
      Entity::EntityFactory &entityFactory)
    {
      std::set<ECS::Entity> activeEntities;

      try {
        for (const auto &serializedEntityData : serializedData) {
          activeEntities.insert(deserializeEntity(serializedEntityData, entityFactory));
        }
        cleanUpEntity(activeEntities);
      } catch (const boost::archive::archive_exception &e) {
        spdlog::error("Caught boost::archive::archive_exception: {}", e.what());
      }
    }

   protected:
    static std::vector<char> serializeEntity(ECS::ComponentManager &componentManager, ECS::Entity entity)
    {
      std::vector<char> serializedData;
      std::ostringstream oss;
      boost::archive::binary_oarchive archive(oss);

      Serializer::serializeComponent<ComponentRType::NetworkedEntity>(componentManager, entity, archive);
      Serializer::serializeComponent<ComponentRType::MetaData>(componentManager, entity, archive);
      Serializer::serializeComponent<ComponentRType::Position>(componentManager, entity, archive);
      Serializer::serializeComponent<ComponentRType::Transform>(componentManager, entity, archive);
      Serializer::serializeComponent<ComponentRType::Displayable>(componentManager, entity, archive);

      std::string dataStr = oss.str();
      serializedData.assign(dataStr.begin(), dataStr.end());
      return serializedData;
    }

    ECS::Entity deserializeEntity(
      const std::vector<char> &serializedData,
      Entity::EntityFactory &entityFactory)
    {
      std::istringstream iss(std::string(serializedData.begin(), serializedData.end()));
      boost::archive::binary_iarchive archive(iss);

      auto componentNE = Serializer::deserializeComponent<ComponentRType::NetworkedEntity>(archive);
      auto componentMD = Serializer::deserializeComponent<ComponentRType::MetaData>(archive);

      auto &componentManager = getEcsRegistry().getComponentManager();
      auto entityOpt = getNetworkedEntityById(componentNE, *componentManager);
      if (entityOpt.has_value()) {
        return updateEntity(entityOpt.value(), archive);
      }
      return createEntity(entityFactory, componentNE, componentMD, archive);
    }

   private:
    ECS::Entity updateEntity(const ECS::Entity &entity, boost::archive::binary_iarchive &archive)
    {
      auto &componentManager = getEcsRegistry().getComponentManager();

      Serializer::deserializeComponentToEntity<ComponentRType::Position>(*componentManager, entity, archive);
      Serializer::deserializeComponentToEntity<ComponentRType::Transform>(*componentManager, entity, archive);
      return entity;
    }

    ECS::Entity createEntity(
      Entity::EntityFactory &entityFactory,
      ComponentRType::NetworkedEntity componentNE,
      ComponentRType::MetaData componentMD,
      boost::archive::binary_iarchive &archive)
    {
      auto &componentManager = getEcsRegistry().getComponentManager();
      const ECS::Entity entity = entityFactory.loadFromNetwork(componentNE, componentMD);

      updateEntity(entity, archive);
      Serializer::deserializeComponentToEntity<ComponentRType::Displayable>(
        *componentManager,
        entity,
        archive);
      auto &comp = componentManager->getComponent<ComponentRType::Displayable>(entity);
      comp = ComponentRType::Displayable(
        comp.assetPath,
        {comp.rectLeft, comp.rectTop, comp.rectWidth, comp.rectHeight});
      return entity;
    }

    void cleanUpEntity(std::set<ECS::Entity> &activeEntities)
    {
      std::set<ECS::Entity> m_garbageEntities {};

      for (auto &entity : m_entities) {
        if (activeEntities.find(entity) == activeEntities.end()) {
          m_garbageEntities.insert(entity);
        }
      }
      for (auto &garbageEntity : m_garbageEntities) {
        m_entities.erase(garbageEntity);
        getEcsRegistry().destroyEntity(garbageEntity);
      }
    }

    std::optional<const ECS::Entity> getNetworkedEntityById(
      ComponentRType::NetworkedEntity id,
      ECS::ComponentManager &componentManager)
    {
      auto it = std::find_if(
        m_entities.begin(),
        m_entities.end(),
        [&componentManager, &id](const ECS::Entity &entity) {
          auto currentId = componentManager.getComponent<ComponentRType::NetworkedEntity>(entity);
          return id == currentId;
        });

      static std::optional<const ECS::Entity> emptyOptional;
      return (it != m_entities.end()) ? std::ref(*it) : emptyOptional;
    }
  };
}; // namespace GameEngine::System
