//
// Created by raphael on 12/22/23.
//

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include "spdlog/spdlog.h"

namespace GameEngine::Asset
{

  class AssetManager {
   public:
    static std::string defaultTextureId;
    static std::string defaultFontId;

    AssetManager();

    static AssetManager& getInstance();

    sf::Texture& getTexture(const std::string& textureId);
    sf::Font& getFont(const std::string& fontId);

    void unloadTexture(const std::string& textureId);
    void unloadFont(const std::string& fontId);

    void loadTexture(const std::string& path, const std::string& textureId);
    void loadFont(const std::string& path, const std::string& fontId);

    void loadAssetsFromDirectories(
      const std::string& textureDirectory,
      const std::string& fontDirectory,
      const std::string& textureFileExtension = ".png",
      const std::string& fontFileExtension = ".ttf");

   private:
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Font> m_fonts;

    bool textureExists(const std::string& textureId) const;
    bool fontExists(const std::string& fontId) const;
  };

  sf::Texture& getTexture(const std::string& textureId = AssetManager::defaultTextureId);
  sf::Font& getFont(const std::string& fontId = AssetManager::defaultFontId);

} // namespace GameEngine::Asset
