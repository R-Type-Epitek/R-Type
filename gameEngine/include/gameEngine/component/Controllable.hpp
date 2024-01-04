//
// Created by raphael on 1/4/24.
//

#pragma once

namespace ComponentRType
{

  /// \brief A component representing if a entity is controllable.
  struct Controllable {
    size_t ControllerNetworkId = 0;
  };

} // namespace ComponentRType