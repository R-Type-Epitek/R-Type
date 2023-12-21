//
// Created by Alexandre Decobert on 21/12/2023.
//

#include "ecs/TextureManager.hpp"

/// \brief Parses the identifier from a given file path.
/// \param const std::string&
/// \return std::string
/// This function extracts and returns the identifier from the provided file path,
/// typically used for texture files. It removes a predefined prefix ("assets/")
/// from the path.
std::string TextureManager::parseIdFromPath(const std::string& path)
{
    std::string prefix = "assets/";
    size_t pos = path.find(prefix);
    if (pos != std::string::npos) {
      return path.substr(pos + prefix.length());
    }
    return path;
}

/// \brief Registers a texture with the given name.
/// \param const std::string&
/// This function registers a new texture under the given name. It asserts that the texture
/// has not already been registered, loads the texture from the file, and stores it.
void TextureManager::registerTexture(std::string const& name)
{
  std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
  texture->loadFromFile(name);
  std::string searched_name = parseIdFromPath(name);
  m_textures[searched_name] = texture;
}

/// \brief Retrieves a shared pointer to a texture based on its name.
/// \param const std::string&
/// \return std::shared_ptr<sf::Texture>
/// This function returns a shared pointer to the texture associated with the given name.
/// If the name includes a specific prefix, it is processed to extract the identifier.
/// If the texture is not found, a default texture is returned.
std::shared_ptr<sf::Texture> TextureManager::getTexture(std::string const& name)
{
  if (name.find("assets/") != std::string::npos) {
    std::string searched_name = parseIdFromPath(name);
    return m_textures[searched_name];
  } else if (m_textures.find(name) != m_textures.end()) {
    return m_textures[name];
  }
  return m_textures["unknown.png"];
}