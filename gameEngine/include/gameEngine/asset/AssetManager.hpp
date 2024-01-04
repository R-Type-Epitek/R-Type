//
// Created by raphael on 12/22/23.
//

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

namespace GameEngine::Asset
{

  class AssetManager {
   public:
    static std::string defaultTextureId;

    AssetManager();

    static AssetManager& getInstance();

    sf::Texture& getTexture(const std::string& textureId);

    void unloadTexture(const std::string& textureId);

    void loadTexture(const std::string& path, const std::string& textureId);

    void loadTexturesFromDirectories(const std::string& directory, const std::string& fileExtension = ".png");

   private:
    std::unordered_map<std::string, sf::Texture> m_textures;

    // Private function to check if the texture exists
    bool textureExists(const std::string& textureId) const;
  };

  sf::Texture& getTexture(const std::string& textureId = AssetManager::defaultTextureId);

} // namespace GameEngine::Asset::AssetManager
