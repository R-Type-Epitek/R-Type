//
// Created by raphael on 11/28/23.
//

#pragma once
#include "Component.hpp"
#include "ComponentArray.hpp"
#include <typeinfo>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <cassert>

class ComponentManager
{
public:
    template<typename T>
    void registerComponent()
    {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Registering component type more than once.");

        m_componentTypes.insert({typeName, m_nextComponentType});
        m_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
        ++m_nextComponentType;
    }

    template<typename T>
    ComponentType getComponentType()
    {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "ComponentRType not registered before use.");

        // Return this component's type - used for creating signatures
        return m_componentTypes[typeName];
    }

    template<typename T>
    void addComponent(Entity entity, T component)
    {
        // Add a component to the array for an entity
        getComponentArray<T>()->insertData(entity, component);
    }

    template<typename T>
    void removeComponent(Entity entity)
    {
        getComponentArray<T>()->removeData(entity);
    }

    template<typename T>
    T& getComponent(Entity entity)
    {
        return getComponentArray<T>()->getData(entity);
    }

    void entityDestroyed(Entity entity)
    {
        for (auto const& pair : m_componentArrays)
        {
            auto const& component = pair.second;
            component->entityDestroyed(entity);
        }
    }

private:
    std::unordered_map<const char*, ComponentType> m_componentTypes{};

    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays{};

    ComponentType m_nextComponentType{};

    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray()
    {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "ComponentRType not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
    }
};