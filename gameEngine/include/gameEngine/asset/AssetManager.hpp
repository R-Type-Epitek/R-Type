//
// Created by raphael on 12/22/23.
//

#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#define LOAD_TEXTURE(x) GameEngine::Asset::AssetManager::AssetManager::getInstance().getTexture(x)
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
    void loadTexturesFormDirectories(std::string const& directory, std::string const& fileExtension = ".png");

    sf::Texture& getTexture(std::string const& textureId);

    void unloadTexture(std::string const& textureId);

   protected:
    void loadTexture(std::string const& path, std::string const& textureId);

   private:
    std::unordered_map<std::string, sf::Texture> m_textures;
  };
} // namespace GameEngine::Asset::AssetManager
