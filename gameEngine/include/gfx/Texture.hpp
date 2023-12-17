//
// Created by lsg on 16/12/23.
//

#pragma once

#include "ITexture.hpp"

class Texture : ITexture {
 public:
  virtual void loadTexture() = 0;
  virtual void unloadTexture() = 0;

 private:
};
