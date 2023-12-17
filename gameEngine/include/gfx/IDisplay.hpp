//
// Created by lsg on 16/12/23.
//

#pragma once

class IDisplay {
 public:
  virtual ~IDisplay() = default;
  virtual void draw() = 0;
  virtual void clear() = 0;

 private:
};