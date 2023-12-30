//
// Created by raphael on 12/24/23.
//

#pragma once
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include <cstdlib>
#include <cstring>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace GameEngine::Network::Serializer
{
  class BaseNetworkComponent {
  public:
    virtual ~BaseNetworkComponent() = default;

  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &, const unsigned int)
    {
      // Base class has no data to serialize
    }
  };

  class EcsSerializer {
  public:
    template<typename T, typename Archive>
    static void serializeComponent(
      GameEngine::ECS::ComponentManager &componentManager,
      const GameEngine::ECS::Entity &entity,
      Archive &archive)
    {
      auto &component = componentManager.getComponent<T>(entity);
      archive << component;
    }

    template<typename T, typename Archive>
    static T deserializeComponent(Archive &archive)
    {
      T component;
      archive >> component;
      return component;
    }

    template<typename T, typename Archive>
    static T &deserializeComponentToEntity(
      GameEngine::ECS::ComponentManager &componentManager,
      const GameEngine::ECS::Entity &entity,
      Archive &archive)
    {
      auto &component = componentManager.getComponent<T>(entity);
      T componentData;
      archive >> componentData;
      component = componentData;
      return componentData;

      //      archive >> component;
      //      return component;
    }
  };
}; // namespace GameEngine::Network::Serializer
