//
// Created by raphael on 11/28/23.
//

#pragma once
#include "Component.hpp"
#include "ComponentArray.hpp"
#include "gameEngine/ecs/component/IComponent.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include <cassert>
#include <memory>
#include <typeinfo>
#include <unordered_map>

namespace GameEngine::ECS {
class ComponentManager {
 public:
  /// \brief Registers a new component type.
  template <typename T>
  void registerComponent() {
    char const* typeName = typeid(T).name();

    assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Registering component type more than once.");

    m_componentTypes.insert({typeName, m_nextComponentType});
    m_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
    ++m_nextComponentType;
  }

  /// \brief Retrieves the type ID of a component.
  /// \return ComponentType
  template <typename T>
  ComponentType getComponentType() {
    char const* typeName = typeid(T).name();

    assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "ComponentRType not registered before use.");

    // Return this component's type - used for creating signatures
    return m_componentTypes[typeName];
  }

  /// \brief Adds a component to an entity.
  /// \param Entity
  /// \param T - Component data
  template <typename T>
  void addComponent(Entity entity, T component) {
    // Add a component to the array for an entity
    getComponentArray<T>()->insertData(entity, component);
  }

  /// \brief Removes a component from an entity.
  /// \param Entity
  template <typename T>
  void removeComponent(Entity entity) {
    getComponentArray<T>()->removeData(entity);
  }

  /// \brief Retrieves a reference to an entity's component.
  /// \param Entity
  /// \return T&
  template <typename T>
  T& getComponent(Entity entity) {
    return getComponentArray<T>()->getData(entity);
  }

  /// \brief Notifies the component arrays that an entity has been destroyed.
  /// \param Entity
  void entityDestroyed(Entity entity) {
    for (auto const& pair : m_componentArrays) {
      auto const& component = pair.second;
      component->entityDestroyed(entity);
    }
  }

  /// \brief Retrieves all components associated with a specific entity.
  /// \param Entity
  /// \return std::unordered_map<const char*, std::shared_ptr<IComponentArray>>
  std::unordered_map<char const*, std::shared_ptr<IComponentArray>> getComponentsWithEntity(Entity entity) {
    std::unordered_map<char const*, std::shared_ptr<IComponentArray>> components;
    for (auto const& pair : m_componentArrays) {
      auto const& component = pair.second;
      if (component->hasEntity(entity)) {
        components.insert({pair.first, component});
      }
    }
    return components;
  }

 private:
  std::unordered_map<char const*, ComponentType> m_componentTypes{};

  std::unordered_map<char const*, std::shared_ptr<IComponentArray>> m_componentArrays{};

  ComponentType m_nextComponentType{};

  template <typename T>
  std::shared_ptr<ComponentArray<T>> getComponentArray() {
    char const* typeName = typeid(T).name();

    assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "ComponentRType not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
  }
};
};  // namespace GameEngine::ECS
