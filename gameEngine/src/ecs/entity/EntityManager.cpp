//
// Created by raphael on 12/4/23.
//

#include "gameEngine/ecs/entity/EntityManager.hpp"
#include <cassert>

namespace GameEngine::ECS
{
  EntityManager::EntityManager()
  {
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
      m_availableEntities.push(entity);
    }
  }

  /// \brief Creates a new entity and returns its ID.
  /// \return Entity
  Entity EntityManager::createEntity()
  {
    assert(m_livingEntityCount < MAX_ENTITIES && "Too many m_entities in existence.");

    Entity id = m_availableEntities.front();
    m_availableEntities.pop();
    ++m_livingEntityCount;

    return id;
  }

  /// \brief Destroys an entity, making its ID available again.
  /// \param Entity
  void EntityManager::destroyEntity(Entity entity)
  {
    assert(entity < MAX_ENTITIES && "Entity out of range.");
    m_signatures[entity].reset();

    m_availableEntities.push(entity);
    --m_livingEntityCount;
  }

  /// \brief Sets the signature of an entity.
  /// \param Entity
  /// \param Signature
  void EntityManager::setSignature(Entity entity, Signature signature)
  {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    m_signatures[entity] = signature;
  }

  /// \brief Gets the signature of an entity.
  /// \param Entity
  /// \return Signature
  Signature EntityManager::getSignature(Entity entity)
  {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    return m_signatures[entity];
  }
}; // namespace GameEngine::ECS