//
// Created by Xavier VINCENT on 17/12/23.
//

#pragma once

#include "RTypeClient.hpp"

namespace Client
{
    class Background {
        public:
            Background() = default;
            Background(sf::Vector2f position, std::string assetPath);
            ~Background() = default;
            Background(Background const &toCopy) = default;
            Background(Background &&toMove) = default;
            Background &operator=(Background const &toCopy) = default;
            Background &operator=(Background &&toMove) = default;

            void draw(sf::RenderWindow &window);

        protected:
        private:
            std::shared_ptr<sf::Sprite> sprite_;
            sf::Texture texture_;
    };
}
