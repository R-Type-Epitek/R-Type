//
// Created by raphael on 12/22/23.
//

#pragma once
#include "Registry.hpp"
#include <memory>

namespace GameEngine::Builder {
class RegistryBuilder {
 public:
  RegistryBuilder();
  std::unique_ptr<GameEngine::ECS::Registry> getResult();

  template <typename T>
  void registerComponent() {
    m_registry->registerComponent<T>();
  };

  void buildSystemRenderer();
  void buildSystemAnimation();
  void buildSystemPhysics();

 private:
  std::unique_ptr<GameEngine::ECS::Registry> m_registry;
};
};  // namespace GameEngine::Builder