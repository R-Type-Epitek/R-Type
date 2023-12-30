//
// Created by raphael on 12/4/23.
//

#pragma once

#include "gameEngine/ecs/Signature.hpp"
#include "gameEngine/ecs/component/Component.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/ecs/entity/EntityManager.hpp"
#include "gameEngine/ecs/system/SystemManager.hpp"
#include <memory>
#include <unordered_map>

namespace GameEngine::ECS
{
  class Registry {
   public:
    Registry()
    {
      m_componentManager = std::make_shared<ComponentManager>();
      m_entityManager = std::make_unique<EntityManager>();
      m_systemManager = std::make_unique<SystemManager>();
    }

    //  Entities
    Entity createEntity()
    {
      return m_entityManager->createEntity();
    }

    void destroyEntity(Entity entity)
    {
      m_entityManager->destroyEntity(entity);

      m_componentManager->entityDestroyed(entity);

      m_systemManager->entityDestroyed(entity);
    }

    //    Components
    template<typename T>
    void registerComponent()
    {
      m_componentManager->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity entity, T component)
    {
      m_componentManager->addComponent<T>(entity, component);

      auto signature = m_entityManager->getSignature(entity);
      signature.set(m_componentManager->getComponentType<T>(), true);
      m_entityManager->setSignature(entity, signature);

      m_systemManager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    void removeComponent(Entity entity)
    {
      m_componentManager->removeComponent<T>(entity);

      auto signature = m_entityManager->getSignature(entity);
      signature.set(m_componentManager->getComponentType<T>(), false);
      m_entityManager->setSignature(entity, signature);

      m_systemManager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& getComponent(Entity entity)
    {
      return m_componentManager->getComponent<T>(entity);
    }

    template<typename T>
    ComponentType getComponentType()
    {
      return m_componentManager->getComponentType<T>();
    }

    //  Systems
    template<typename T>
    std::shared_ptr<T> registerSystem()
    {
      return m_systemManager->registerSystem<T>();
    }

    template<typename T>
    void setSystemSignature(Signature signature)
    {
      m_systemManager->setSignature<T>(signature);
    }

    std::unordered_map<char const*, std::shared_ptr<System>> getSystems()
    {
      return m_systemManager->getSystems();
    }

    std::unordered_map<char const*, Signature> getSignatures()
    {
      return m_systemManager->getSignatures();
    }

    Signature getSystemSignature(char const* name)
    {
      return m_systemManager->getSignature(name);
    }

    Signature getEntitySignature(Entity& entity)
    {
      return m_entityManager->getSignature(entity);
    }

    std::unordered_map<char const*, std::shared_ptr<IComponentArray>> getComponents(Entity& entity)
    {
      return m_componentManager->getComponentsWithEntity(entity);
    }

    std::shared_ptr<ComponentManager>& getComponentManager()
    {
      return m_componentManager;
    }

   private:
    std::shared_ptr<ComponentManager> m_componentManager;
    std::unique_ptr<EntityManager> m_entityManager;
    std::unique_ptr<SystemManager> m_systemManager;
  };
}; // namespace GameEngine::ECS