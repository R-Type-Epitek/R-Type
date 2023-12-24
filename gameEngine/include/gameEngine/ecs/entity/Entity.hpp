//
// Created by raphael on 11/28/23.
//

#pragma once
#include <cstddef>
#include <cstdint>

namespace GameEngine::ECS
{
  using Entity = std::uint32_t;

  size_t constexpr MAX_ENTITIES = 5000;
} // namespace GameEngine::ECS
