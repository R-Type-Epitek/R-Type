//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once
#include "gameEngine/asset/AssetManager.hpp"
#include "gameEngine/network/Serializer.hpp"

#include <boost/serialization/access.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace ComponentRType
{

  namespace assetManager = GameEngine::Asset;

  struct Displayable : public GameEngine::Network::Serializer::BaseNetworkComponent {
    friend class boost::serialization::access;
    sf::Sprite sprite;
    std::string assetPath = "";
    int rectTop = -1;
    int rectLeft = -1;
    int rectWidth = -1;
    int rectHeight = -1;

    Displayable()
    {
      sprite.setTexture(assetManager::getTexture(this->assetPath));
      if (rectWidth > 0 || rectHeight > 0)
        sprite.setTextureRect(sf::IntRect(rectLeft, rectTop, rectWidth, rectHeight));
    }

    Displayable(std::string assetPath)
      : assetPath(std::move(assetPath))
    {
      sprite.setTexture(assetManager::getTexture(this->assetPath));
    }

    Displayable(std::string assetPath, sf::IntRect const& rect)
      : assetPath(std::move(assetPath))
      , rectTop(rect.top)
      , rectLeft(rect.left)
      , rectWidth(rect.width)
      , rectHeight(rect.height)
    {
      sprite.setTexture(assetManager::getTexture(this->assetPath));
      if (rect.width > 0 || rect.height > 0)
        sprite.setTextureRect(rect);
    }

    template<class Archive>
    void serialize(Archive& archive, const unsigned int)
    {
      boost::serialization::base_object<GameEngine::Network::Serializer::BaseNetworkComponent>(*this);
      archive& BOOST_SERIALIZATION_NVP(assetPath);
      archive& BOOST_SERIALIZATION_NVP(rectTop);
      archive& BOOST_SERIALIZATION_NVP(rectLeft);
      archive& BOOST_SERIALIZATION_NVP(rectWidth);
      archive& BOOST_SERIALIZATION_NVP(rectHeight);
    }
  };

} // namespace ComponentRType
