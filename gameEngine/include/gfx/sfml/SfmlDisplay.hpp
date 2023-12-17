//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once

#include <SFML/Graphics.hpp>

class SfmlDisplay {

 public:
  SfmlDisplay() = default;
  ~SfmlDisplay() = default;

  void display(sf::RenderWindow& window);
};