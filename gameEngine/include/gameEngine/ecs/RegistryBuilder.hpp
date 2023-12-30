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
    std::unique_ptr<GameEngine::ECS::Registry> getResult();

    template<typename T>
    void registerComponent()
    {
      m_registry->registerComponent<T>();
    };

    void registerAllMandatoryComponent();
    void buildSystemRenderer();
    void buildSystemAnimation();
    void buildSystemPhysics();
    void buildSystemKeyboard();
    void buildSystemEcsSerializer();

   private:
    std::unique_ptr<GameEngine::ECS::Registry> m_registry;
  };
}; // namespace GameEngine::Builder