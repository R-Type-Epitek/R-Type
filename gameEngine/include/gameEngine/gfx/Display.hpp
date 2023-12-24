//
// Created by lsg on 16/12/23.
//

#pragma once

#include "IDisplay.hpp"

class Display : public IDisplay {
public:
  void draw();
  void clear();

private:
};