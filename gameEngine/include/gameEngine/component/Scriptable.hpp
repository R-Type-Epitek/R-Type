//
// Created by raphael on 1/4/24.
//

#pragma once

#include <string>

namespace ComponentRType
{

  /// \brief A component representing if a entity is scriptable.
  struct Scriptable {
    Scriptable() = default;
    Scriptable(std::string scriptName)
      : scriptName(std::move(scriptName))
    {
    }

    std::string scriptName;
  };
} // namespace ComponentRType
