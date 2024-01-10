//
// Created by raphael on 11/28/23.
//

#pragma once

#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include <set>
#include <utility>

namespace GameEngine::ECS
{
  class RegistryHolder {
   public:
    virtual ~RegistryHolder() = default;

    void setEcsRegistry(std::shared_ptr<Registry> ecsRegistry)
    {
      m_ecsRegistry = std::move(ecsRegistry);
    }

    Registry& getEcsRegistry()
    {
      return *m_ecsRegistry;
    }

    std::shared_ptr<Registry> getSharedEcsRegistry()
    {
      return m_ecsRegistry;
    }

   private:
    std::shared_ptr<Registry> m_ecsRegistry;
  };

} // namespace GameEngine::ECS
