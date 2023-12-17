//
// Created by X-VINCENT on 12/17/23.
//

#pragma once

#include "RTypeClient.hpp"

namespace Client
{
    class InputText {
        public:
            InputText() = default;
            InputText(
                sf::Vector2f position,
                sf::Vector2f size,
                std::string fontPath,
                std::string defaultText
            );
            ~InputText() = default;
            InputText(InputText const &toCopy) = default;
            InputText(InputText &&toMove) = default;
            InputText &operator=(InputText const &toCopy) = default;
            InputText &operator=(InputText &&toMove) = default;
            std::shared_ptr<sf::RectangleShape> getShape();
            void draw(sf::RenderWindow &window);
            void startInput();
            void endInput();
            std::string getInput();
            void setInput(char input);
            bool isClicked() const;
            void popInput();

        protected:
        private:
            std::shared_ptr<sf::RectangleShape> shape_;
            std::string input_;
            std::string fontPath_;
            sf::Vector2f positionText_;
            bool isClicked_{false};
    };
}
