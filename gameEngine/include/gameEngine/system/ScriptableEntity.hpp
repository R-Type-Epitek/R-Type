//
// Created by raphael on 1/10/24.
//

#pragma once

#include "gameEngine/component/Scriptable.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/event/EventRegistry.hpp"
#include "gameEngine/entity/EntityFactory.hpp"

namespace GameEngine::System
{

  class ScriptableEntity
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder {
   public:
    void update(Entity::EntityFactory& entityFactory, int df)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto& scriptManager = entityFactory.getScriptManager();

      for (auto const& entity : m_entities) {
        auto& scriptData = componentManager->getComponent<ComponentRType::Scriptable>(entity);
        auto script = scriptManager.getScript(scriptData.scriptName);

        script->attachEntity(entity);
        if (!script->isConfigured()) {
          script->attachEcsRegistry(getSharedEcsRegistry());
          script->attachEventRegistry(getSharedEventRegistry());
          script->subscribeEvent();
        }
        script->execute(df);
      }
    }
  };
} // namespace GameEngine::System
