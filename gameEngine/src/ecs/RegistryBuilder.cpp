//
// Created by raphael on 12/22/23.
//

//
// Created by raphael on 12/22/23.
//

#pragma once
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "gameEngine/system/Animation.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/Renderer.hpp"
#include <memory>
#include <utility>

namespace GameEngine::Builder {

RegistryBuilder::RegistryBuilder() : m_registry{std::make_unique<GameEngine::ECS::Registry>()} {}

std::unique_ptr<GameEngine::ECS::Registry> RegistryBuilder::getResult() { return std::move(m_registry); }

void RegistryBuilder::buildSystemRenderer() {
  GameEngine::ECS::Signature signature;
  m_registry->registerSystem<GameEngine::System::Renderer>();
  //  System components
  signature.set(m_registry->getComponentType<ComponentRType::Sprite>());
  m_registry->setSystemSignature<GameEngine::System::Renderer>(signature);
}

void RegistryBuilder::buildSystemAnimation() {
  GameEngine::ECS::Signature signature;
  m_registry->registerSystem<GameEngine::System::Animation>();
  //  System components
  signature.set(m_registry->getComponentType<ComponentRType::Sprite>());
  signature.set(m_registry->getComponentType<ComponentRType::Transform>());
  m_registry->setSystemSignature<GameEngine::System::Animation>(signature);
}

void RegistryBuilder::buildSystemPhysics() {
  GameEngine::ECS::Signature signature;
  m_registry->registerSystem<GameEngine::System::Physics>();
  //  System components
  signature.set(m_registry->getComponentType<ComponentRType::Gravity>());
  signature.set(m_registry->getComponentType<ComponentRType::Transform>());
  m_registry->setSystemSignature<GameEngine::System::Physics>(signature);
}

};  // namespace GameEngine::Builder