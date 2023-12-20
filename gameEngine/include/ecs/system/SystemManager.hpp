//
// Created by raphael on 11/28/23.
//

#pragma once
#include "System.hpp"
#include "ecs/Signature.hpp"
#include "ecs/entity/Entity.hpp"
#include <cassert>
#include <memory>
#include <unordered_map>

class SystemManager {
 public:
  template <typename T>
  std::shared_ptr<T> registerSystem() {
    char const* typeName = typeid(T).name();

    assert(m_systems.find(typeName) == m_systems.end() &&
           "Registering system more than once.");

    auto system = std::make_shared<T>();
    m_systems.insert({typeName, system});
    return system;
  }

  template <typename T>
  void setSignature(Signature signature) {
    char const* typeName = typeid(T).name();

    assert(m_systems.find(typeName) != m_systems.end() &&
           "System used before registered.");

    m_signatures.insert({typeName, signature});
  }

  void entityDestroyed(Entity entity) {
    for (auto const& pair : m_systems) {
      auto const& system = pair.second;

      system->m_entities.erase(entity);
    }
  }

  void entitySignatureChanged(Entity entity, Signature entitySignature) {
    for (auto const& pair : m_systems) {
      auto const& type = pair.first;
      auto const& system = pair.second;
      auto const& systemSignature = m_signatures[type];

      if ((entitySignature & systemSignature) == systemSignature) {
        system->m_entities.insert(entity);
      } else {
        system->m_entities.erase(entity);
      }
    }
  }

 private:
  std::unordered_map<char const*, Signature> m_signatures{};

  std::unordered_map<char const*, std::shared_ptr<System>> m_systems{};
};
