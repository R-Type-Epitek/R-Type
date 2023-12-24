//
// Created by raphael on 11/28/23.
//

#pragma once

#include "Component.hpp"
#include "IComponent.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include <array>
#include <cassert>
#include <unordered_map>

namespace GameEngine::ECS {

template <typename T>
class ComponentArray : public IComponentArray {
 public:
  /// \brief Inserts new component data for an entity.
  /// \param Entity
  /// \param T - Component data
  void insertData(Entity entity, T component) {
    assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end());

    size_t newIndex = mSize;
    m_entityToIndexMap[entity] = newIndex;
    m_indexToEntityMap[newIndex] = entity;
    m_componentArray[newIndex] = component;
    ++mSize;
  }

  /// \brief Removes component data of a specific entity.
  /// \param Entity
  void removeData(Entity entity) {
    assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end());

    size_t indexOfRemovedEntity = m_entityToIndexMap[entity];
    size_t indexOfLastElement = mSize - 1;
    m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];

    Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
    m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
    m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

    m_entityToIndexMap.erase(entity);
    m_indexToEntityMap.erase(indexOfLastElement);

    --mSize;
  }

  /// \brief Checks if a component exists for an entity.
  /// \param Entity
  /// \return bool
  bool hasEntity(Entity entity) override { return m_entityToIndexMap.find(entity) != m_entityToIndexMap.end(); }

  /// \brief Retrieves the component data for an entity.
  /// \param Entity
  /// \return T&
  T& getData(Entity entity) {
    assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end());

    return m_componentArray[m_entityToIndexMap[entity]];
  }

  /// \brief Handles the case when an entity is destroyed.
  /// \param Entity
  void entityDestroyed(Entity entity) override {
    if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end()) {
      removeData(entity);
    }
  }

 private:
  std::array<T, ECS::MAX_COMPONENTS> m_componentArray{};

  std::unordered_map<Entity, size_t> m_entityToIndexMap;

  std::unordered_map<size_t, Entity> m_indexToEntityMap;

  size_t mSize{};
};
}  // namespace GameEngine::ECS