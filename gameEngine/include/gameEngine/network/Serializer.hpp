//
// Created by raphael on 12/24/23.
//

#pragma once
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include <cstdlib>
#include <cstring>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

namespace GameEngine::Network::Serializer
{
  class EcsSerializer {
  public:
    template<typename T, typename Archive>
    static void serializeComponent(
      std::shared_ptr<GameEngine::ECS::ComponentManager> &componentManager,
      const GameEngine::ECS::Entity &entity,
      Archive &archive)
    {
      auto &component = componentManager->getComponent<T>(entity);
      archive << component;
    }

    template<typename T>
    static void deserializeComponent(
      std::shared_ptr<GameEngine::ECS::ComponentManager> &componentManager,
      const std::vector<char> &serializedData,
      size_t &currentIndex)
    {
      std::istringstream inputStream;
      inputStream.rdbuf()->pubsetbuf(
        const_cast<char *>(&serializedData[currentIndex]),
        serializedData.size() - currentIndex);

      boost::archive::text_iarchive const currentArchive(inputStream);
      T component;
      currentArchive >> component;

      // Add the deserialized component to the entity
      //      auto entity = createEntity(); // Implement this function to create an entity
      //      componentManager->addComponent<T>(entity, std::move(component));

      currentIndex += inputStream.tellg();
    }

    // Helper function to append a type identifier to the buffer
    template<typename T>
    static void appendTypeIdentifier(std::vector<char> &buffer)
    {
      int typeId = getTypeIdentifier<T>();
      buffer.insert(
        buffer.end(),
        reinterpret_cast<char *>(&typeId),
        reinterpret_cast<char *>(&typeId) + sizeof(int));
    }

    // Helper function to append serialized data to the buffer
    static void appendSerializedData(const std::string &data, std::vector<char> &buffer)
    {
      buffer.insert(buffer.end(), data.begin(), data.end());
    }

    // Helper function to get a unique type identifier for each component type
    template<typename T>
    static int getTypeIdentifier()
    {
      static int typeIdCounter = 0;
      static const int typeId = typeIdCounter++;
      return typeId;
    }
  };
}