//
// Created by raphael on 12/24/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>

namespace boost::serialization
{

  template<class Archive>
  void serialize(Archive &archive, sf::Vector2f &vector, const unsigned int)
  {
    archive & vector.x;
    archive & vector.y;
  }

} // namespace boost::serialization

namespace GameEngine::Network::Serializer
{

  class BaseNetworkComponent {
   public:
    friend class boost::serialization::access;

    virtual ~BaseNetworkComponent() = default;

   private:
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
      T componentData = deserializeComponent<T>(archive);

      component = componentData;
      return component;
    }
  };
}; // namespace GameEngine::Network::Serializer
