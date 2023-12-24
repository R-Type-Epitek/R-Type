//
// Created by raphael on 12/24/23.
//

#pragma once

#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/network/Serializer.hpp"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace GameEngine::System
{
  class EcsSerializer : public GameEngine::ECS::System {
    using Serializer = GameEngine::Network::Serializer::EcsSerializer;

  public:
    std::vector<std::vector<char>> serialise(GameEngine::ECS::Registry &registry)
    {
      auto &componentManager = registry.getComponentManager();
      std::vector<std::vector<char>> serializedData;

      for (auto const &entity : m_entities) {
        std::ostringstream outputStream;
        boost::archive::text_oarchive currentArchive(outputStream);
        std::vector<char> currentSerializedData;

        // Serialize Components
        Serializer::serializeComponent<ComponentRType::MetaData>(componentManager, entity, currentArchive);
        Serializer::appendTypeIdentifier<ComponentRType::MetaData>(currentSerializedData);

        Serializer::serializeComponent<ComponentRType::MetaDataTest>(
          componentManager,
          entity,
          currentArchive);
        Serializer::appendTypeIdentifier<ComponentRType::MetaDataTest>(currentSerializedData);

        Serializer::appendSerializedData(outputStream.str(), currentSerializedData);
        serializedData.push_back(currentSerializedData);
      }

      return serializedData;
    }

    void deserialize(GameEngine::ECS::Registry &registry, std::vector<std::vector<char>> serializedData)
    {
      //      auto &componentManager = registry.getComponentManager();
      //
      //      for (const auto &entityData : serializedData) {
      //        size_t currentIndex = 0;
      //
      //        // Deserialize and extract the entity ID
      //        GameEngine::ECS::Entity entity;
      //        Serializer::deserializeComponent<GameEngine::ECS::Entity>(
      //          componentManager, entityData, currentIndex);
      //
      //        if (componentManager->entityExists(entity)) {
      //          // If the entity exists, update its components
      //          GameEngine::Network::Serializer::EcsSerializer::deserializeComponent<ComponentRType::MetaData>(
      //            componentManager, entityData, currentIndex);
      //          GameEngine::Network::Serializer::EcsSerializer::deserializeComponent<ComponentRType::MetaDataTest>(
      //            componentManager, entityData, currentIndex);
      //          // Add more deserializeComponent calls for other components
      //
      //        } else {
      //          // If the entity doesn't exist, create it
      //          GameEngine::Network::Serializer::EcsSerializer::deserializeComponent<ComponentRType::MetaData>(
      //            componentManager, entityData, currentIndex);
      //          GameEngine::Network::Serializer::EcsSerializer::deserializeComponent<ComponentRType::MetaDataTest>(
      //            componentManager, entityData, currentIndex);
      //        }
    }
  };
}; // namespace GameEngine::System
