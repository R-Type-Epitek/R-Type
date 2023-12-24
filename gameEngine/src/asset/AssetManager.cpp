//
// Created by raphael on 12/22/23.
//

#include "gameEngine/asset/AssetManager.hpp"
#include <exception>
#include <filesystem>
#include <iostream>
#include <string>

namespace GameEngine::Asset::AssetManager
{
  void AssetManager::loadTexturesFormDirectories(
    std::string const& directory,
    std::string const& fileExtension)
  {
    for (auto const& entry : std::filesystem::directory_iterator(directory)) {
      if (entry.path().extension() != fileExtension) {
        continue;
      } else {
        loadTexture(entry.path().string(), entry.path().stem().string());
      }
    }
  }

  sf::Texture& AssetManager::getTexture(std::string const& textureId)
  {
    auto it = m_textures.find(textureId);
    if (it != m_textures.end()) {
      return it->second;
    } else {
      throw std::out_of_range("Texture not found: " + textureId);
    }
  }

  void AssetManager::unloadTexture(std::string const& textureId)
  {
    m_textures.erase(textureId);
  }

  void AssetManager::loadTexture(
    std::string const& path,
    std::string const& textureId)
  {
    sf::Texture texture;
    if (texture.loadFromFile(path)) {
      m_textures[textureId] = texture;
    } else {
      std::cerr << "Failed to load texture: " << path << std::endl;
      throw std::exception();
    }
  }
}; // namespace GameEngine::Asset::AssetManager