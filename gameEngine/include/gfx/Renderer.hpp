//
// Created by lsg on 12/12/23.
//

#pragma once
#include "sfml/SfmlRenderer.hpp"

class Renderer : SfmlRenderer {
 public:
  Renderer();
  ~Renderer();
  void clear() override;

 private:
};