//
// Created by raphael on 12/22/23.
//

#include "gameEngine/asset/AssetManager.hpp"

#include <exception>
#include <filesystem>
#include <iostream>
#include <string>
#include "spdlog/spdlog.h"

#include <exception>
#include <filesystem>

namespace GameEngine::Asset
{

  std::string AssetManager::defaultTextureId = "gameEngine/assets/defaultTexture.png";
  std::string AssetManager::defaultFontId = "game/rtype/assets/font/nasalization-rg.ttf";

  sf::Texture& getTexture(const std::string& textureId)
  {
    return AssetManager::getInstance().getTexture(textureId);
  }

  sf::Font& getFont(const std::string& fontId)
  {
    return AssetManager::getInstance().getFont(fontId);
  }

  AssetManager::AssetManager()
  {
    loadTexture(defaultTextureId, defaultTextureId);
    loadFont(defaultFontId, defaultFontId);
  }

  AssetManager& AssetManager::getInstance()
  {
    static AssetManager instance;
    return instance;
  }

  sf::Texture& AssetManager::getTexture(const std::string& textureId)
  {
    if (textureId.empty())
      return m_textures[defaultTextureId];

    if (!textureExists(textureId)) {
      loadTexture(textureId, textureId);
    }
    return m_textures[textureId];
  }

  sf::Font& AssetManager::getFont(const std::string& fontId)
  {
    if (fontId.empty())
      return m_fonts[defaultFontId];

    if (!fontExists(fontId)) {
      loadFont(fontId, fontId);
    }
    return m_fonts[fontId];
  }

  void AssetManager::unloadTexture(const std::string& textureId)
  {
    auto it = m_textures.find(textureId);
    if (it != m_textures.end()) {
      m_textures.erase(it);
    }
  }

  void AssetManager::unloadFont(const std::string& fontId)
  {
    auto it = m_fonts.find(fontId);
    if (it != m_fonts.end()) {
      m_fonts.erase(it);
    }
  }

  void AssetManager::loadTexture(const std::string& path, const std::string& textureId)
  {
    sf::Texture texture;
    if (texture.loadFromFile(path)) {
      m_textures[textureId] = texture;
    } else {
      spdlog::error("[AssetManager::loadTexture] Failed to load texture: {}", path);
    }
  }

  void AssetManager::loadFont(const std::string& path, const std::string& fontId)
  {
    sf::Font font;
    if (font.loadFromFile(path)) {
      m_fonts[fontId] = font;
    } else {
      spdlog::error("[AssetManager::loadFont] Failed to load font: {}", path);
    }
  }

  void AssetManager::loadAssetsFromDirectories(
    const std::string& textureDirectory,
    const std::string& fontDirectory,
    const std::string& textureFileExtension,
    const std::string& fontFileExtension)
  {
    namespace fs = std::filesystem;

    for (const auto& entry : fs::directory_iterator(textureDirectory)) {
      if (fs::is_regular_file(entry) && entry.path().extension() == textureFileExtension) {
        const std::string texturePath = entry.path().string();
        const std::string textureId = entry.path().stem().string();
        loadTexture(texturePath, textureId);
      }
    }

    for (const auto& entry : fs::directory_iterator(fontDirectory)) {
      if (fs::is_regular_file(entry) && entry.path().extension() == fontFileExtension) {
        const std::string fontPath = entry.path().string();
        const std::string fontId = entry.path().stem().string();
        loadFont(fontPath, fontId);
      }
    }
  }

  bool AssetManager::textureExists(const std::string& textureId) const
  {
    return m_textures.find(textureId) != m_textures.end();
  }

  bool AssetManager::fontExists(const std::string& fontId) const
  {
    return m_fonts.find(fontId) != m_fonts.end();
  }

} // namespace GameEngine::Asset
