//
// Created by raphael on 12/22/23.
//

#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

#define LOAD_TEXTURE(x) GameEngine::Asset::AssetManager::AssetManager::getInstance().loadTexture(x, x)
#define LOAD_TEXTURE_DIR(x, y) \
  GameEngine::Asset::AssetManager::AssetManager::getInstance().loadTexturesFromDirectories(x, y)
#define GET_TEXTURE(x) GameEngine::Asset::AssetManager::AssetManager::getInstance().getTexture(x)

#define DEFAULT_TEXTURE "assets/bobross.jpg"

namespace GameEngine::Asset::AssetManager
{

  class AssetManager {
   public:
    static AssetManager& getInstance()
    {
      static AssetManager instance;
      return instance;
    }

    AssetManager()
    {
      loadTexture(DEFAULT_TEXTURE, DEFAULT_TEXTURE);
    }

    void loadTexturesFromDirectories(std::string const& directory, const std::string& fileExtension = ".png");

    sf::Texture& getTexture(std::string const& textureId);

    void unloadTexture(std::string const& textureId);

    void loadTexture(std::string const& path, std::string const& textureId);

   private:
    std::unordered_map<std::string, sf::Texture> m_textures;
  };
} // namespace GameEngine::Asset::AssetManager
