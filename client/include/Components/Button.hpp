//
// Created by Xavier VINCENT on 17/12/23.
//

#pragma once

#include "RTypeClient.hpp"

namespace Client
{
    class Button {
        public:
            Button() = default;
            Button(
                sf::Vector2f position,
                sf::Vector2f size,
                std::string assetPath
            );
            ~Button() = default;
            Button(Button const &toCopy) = default;
            Button(Button &&toMove) = default;
            Button &operator=(Button const &toCopy) = default;
            Button &operator=(Button &&toMove) = default;
            std::shared_ptr<sf::RectangleShape> getShape();
            void draw(sf::RenderWindow &window);
            void isClicked();
            void isReleased();

        protected:
        private:
            std::shared_ptr<sf::Sprite> sprite_;
            std::shared_ptr<sf::RectangleShape> shape_;
            sf::Texture texture_;
            int alpha_{250};
    };
}
