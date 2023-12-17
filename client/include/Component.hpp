//
// Created by edouard on 12/12/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <memory>
#include <optional>
#include <functional>

namespace Client {
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
        private:
            std::shared_ptr<sf::Sprite> sprite_;
            sf::Texture texture_;
    };

    class Button {
        public:
            Button() = default;
            Button(sf::Vector2f position, sf::Vector2f size, std::string assetPath);
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
