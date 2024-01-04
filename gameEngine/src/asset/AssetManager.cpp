//
// Created by raphael on 12/22/23.
//

#include "gameEngine/asset/AssetManager.hpp"

#include <exception>
#include <filesystem>
#include <iostream>
#include <string>
#include "spdlog/spdlog.h"

namespace GameEngine::Asset
{

  std::string AssetManager::defaultTextureId = "assets/bobross.jpg";

  sf::Texture& getTexture(const std::string& textureId)
  {
    return AssetManager::getInstance().getTexture(textureId);
  }

  AssetManager::AssetManager()
  {
    loadTexture(defaultTextureId, defaultTextureId);
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

  void AssetManager::unloadTexture(const std::string& textureId)
  {
    auto it = m_textures.find(textureId);
    if (it != m_textures.end()) {
      m_textures.erase(it);
    }
  }

  void AssetManager::loadTexture(const std::string& path, const std::string& textureId)
  {
    sf::Texture texture;
    if (texture.loadFromFile(path)) {
      m_textures[textureId] = texture;
    } else {
      spdlog::error("[AssetManager::loadTexture]Failed to load texture: {}", path);
    }
  }

  void AssetManager::loadTexturesFromDirectories(
    const std::string& directory,
    const std::string& fileExtension)
  {
    namespace fs = std::filesystem;

    for (const auto& entry : fs::directory_iterator(directory)) {
      if (fs::is_regular_file(entry) && entry.path().extension() == fileExtension) {
        const std::string texturePath = entry.path().string();
        const std::string textureId = entry.path().stem().string();
        loadTexture(texturePath, textureId);
      }
    }
  }

  bool AssetManager::textureExists(const std::string& textureId) const
  {
    return m_textures.find(textureId) != m_textures.end();
  }

} // namespace GameEngine::Asset::AssetManager