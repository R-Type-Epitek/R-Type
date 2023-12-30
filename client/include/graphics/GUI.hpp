//
// Created by raphael on 12/20/23.
//

#pragma once
#include "gameEngine/UI/Window.hpp"

#include <string>

namespace Client
{

  class GUI : public GameEngine::UI::Window {
   public:
    GUI(int width, int height, std::string& name, float screenRatio);
  };
} // namespace Client
