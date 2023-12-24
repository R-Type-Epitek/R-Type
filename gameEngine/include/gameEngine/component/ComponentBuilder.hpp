//
// Created by Alexandre Decobert on 21/12/2023.
//

#pragma once
#include <iostream>
#include <utility>

namespace GameEngine::Component {

class ComponentBuilder {
 public:
  ComponentBuilder() = default;
  ~ComponentBuilder() = default;

  template <typename MediatorType, typename Entity, typename FirstComponent, typename... Rest>
  static void createEntity(MediatorType& mediator, Entity entity, FirstComponent&& first, Rest&&... rest) {
    std::cout << "Type of std::forward<FirstComponent>(first) = " << typeid(std::forward<FirstComponent>(first)).name()
              << std::endl;
    mediator.addComponent(entity, std::forward<FirstComponent>(first));

    if constexpr (sizeof...(rest) > 0) {
      createEntity(mediator, entity, std::forward<Rest>(rest)...);
    }
  }
};

}  // namespace GameEngine::Component
