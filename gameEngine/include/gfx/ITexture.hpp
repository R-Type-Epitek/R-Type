//
// Created by lsg on 16/12/23.
//

#pragma once

class ITexture {
 public:
  virtual ~ITexture() = default;
  virtual void loadTexture() = 0;
  virtual void unloadTexture() = 0;

 private:
};
