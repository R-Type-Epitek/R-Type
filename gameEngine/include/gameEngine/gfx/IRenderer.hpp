//
// Created by lsg on 12/12/23.
//

#pragma once
#include "Renderer.hpp"

class IRenderer : Renderer {
public:
  virtual ~IRenderer() = default;
  virtual void clear() = 0;
};