//
// Created by Alexandre Decobert on 16/12/2023.
//

#include <chrono>


namespace MathRType {
  class Physics {
  public:
    static void update(std::chrono::duration<double> delta);
  };
}