//
// Created by raphael on 12/20/23.
//
#include "RTypeClient.hpp"

namespace Client
{
  GUI::GUI(int width, int height, std::string& name, float screenRatio)
    : GameEngine::UI::Window(width, height, name, screenRatio)
  {
  }
} // namespace Client
