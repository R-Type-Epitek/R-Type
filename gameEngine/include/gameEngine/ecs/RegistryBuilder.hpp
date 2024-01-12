//
// Created by raphael on 12/22/23.
//

#pragma once
#include "Registry.hpp"

#include <memory>

namespace GameEngine::Builder
{
  class RegistryBuilder {
   public:
    RegistryBuilder();
    std::shared_ptr<GameEngine::ECS::Registry> getResult();
    void buildFrom(std::shared_ptr<GameEngine::ECS::Registry> existingRegistry);

    template<typename T>
    void registerComponent()
    {
      m_registry->registerComponent<T>();
    };

    void registerAllMandatoryComponent();

    void buildSystemAnimation();
    void buildSystemCollider();
    void buildSystemEcsSerializer();
    void buildSystemControlableEntity();
    void buildSystemInputCatcher();
    void buildSystemNetworkEventPusher();
    void buildSystemParallax();
    void buildSystemPhysics();
    void buildSystemRenderer();
    void buildSystemTextRenderer();
    void buildSystemSpawning();
    void buildSystemUI();

   private:
    void feedSystemHolder();
    std::shared_ptr<GameEngine::ECS::Registry> m_registry;
  };
}; // namespace GameEngine::Builder
