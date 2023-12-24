//
// Created by Alexandre Decobert on 21/12/2023.
//

#pragma once

#include <utility>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include <cassert>

class TextureManager {
 public:
  TextureManager() {
    registerTexture("assets/unknown.png");
  }
  ~TextureManager() = default;

  static TextureManager& getInstance() {
    static TextureManager instance;
    return instance;
  }

  static std::string parseIdFromPath(const std::string& path);

  void registerTexture(std::string const& name);
  std::shared_ptr<sf::Texture> getTexture(std::string const& name);

 private:
  std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
};
