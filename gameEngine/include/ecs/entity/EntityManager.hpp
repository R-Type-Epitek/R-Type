//
// Created by raphael on 11/28/23.
//

#pragma once

#include <queue>
#include <array>
#include "Entity.hpp"
#include "ecs/Signature.hpp"

class EntityManager
{
public:
    EntityManager();

    Entity createEntity();

    void destroyEntity(Entity entity);

    void setSignature(Entity entity, Signature signature);

    Signature getSignature(Entity entity);

private:
    std::queue<Entity> m_availableEntities{};

    std::array<Signature, MAX_ENTITIES> m_signatures{};

    uint32_t m_livingEntityCount{};
};
