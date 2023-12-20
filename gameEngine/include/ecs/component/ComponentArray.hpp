//
// Created by raphael on 11/28/23.
//

#pragma once

#include "Component.hpp"
#include "IComponent.hpp"
#include "ecs/entity/Entity.hpp"
#include <array>
#include <cassert>
#include <unordered_map>

template <typename T>
class ComponentArray : public IComponentArray {
 public:
  void insertData(Entity entity, T component) {
    assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end());

    size_t newIndex = mSize;
    m_entityToIndexMap[entity] = newIndex;
    m_indexToEntityMap[newIndex] = entity;
    m_componentArray[newIndex] = component;
    ++mSize;
  }

  void removeData(Entity entity) {
    assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end());

    size_t indexOfRemovedEntity = m_entityToIndexMap[entity];
    size_t indexOfLastElement = mSize - 1;
    m_componentArray[indexOfRemovedEntity] =
        m_componentArray[indexOfLastElement];

    Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
    m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
    m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

    m_entityToIndexMap.erase(entity);
    m_indexToEntityMap.erase(indexOfLastElement);

    --mSize;
  }

  T& getData(Entity entity) {
    assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end());

    return m_componentArray[m_entityToIndexMap[entity]];
  }

  void entityDestroyed(Entity entity) override {
    if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end()) {
      removeData(entity);
    }
  }

 private:
  std::array<T, MAX_ENTITIES> m_componentArray;

  std::unordered_map<Entity, size_t> m_entityToIndexMap;

  std::unordered_map<size_t, Entity> m_indexToEntityMap;

  size_t mSize{};
};
