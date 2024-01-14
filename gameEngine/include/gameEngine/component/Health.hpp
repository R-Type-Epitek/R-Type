//
// Created by sgLeopold on 14/01/2024.
//

#pragma once

namespace ComponentRType
{
  static const int kdefaultDamage = 50;

  struct Health {
    int value;
    bool isAlive;
    int damage = kdefaultDamage;
  };
} // namespace ComponentRType