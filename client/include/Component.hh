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

namespace client {
    class Background {
        public:
            Background() = default;
            Background(sf::Vector2f position, std::string &asset_path);
            ~Background() = default;
            Background(Background const &to_copy) = default;
            Background(Background &&to_move) = default;
            Background &operator=(Background const &to_copy) = default;
            Background &operator=(Background &&to_move) = default;

            void draw(sf::RenderWindow &window);
        private:
            std::shared_ptr<sf::Sprite> sprite_;
            sf::Texture texture_;
    };

    class Button {
        public:
            Button() = default;
            Button(sf::Vector2f position, sf::Vector2f size, std::string &asset_path);
            ~Button() = default;
            Button(Button const &to_copy) = default;
            Button(Button &&to_move) = default;
            Button &operator=(Button const &to_copy) = default;
            Button &operator=(Button &&to_move) = default;
            std::shared_ptr<sf::RectangleShape> get_shape();
            void draw(sf::RenderWindow &window);
            void is_clicked();
            void is_release();

        private:
            std::shared_ptr<sf::Sprite> sprite_;
            std::shared_ptr<sf::RectangleShape> shape_;
            sf::Texture texture_;
            int alpha_{250};
    };

    class InputText {
        public:
            InputText() = default;
            InputText(sf::Vector2f position, sf::Vector2f size, std::string &font_path, std::string &default_text);
            ~InputText() = default;
            InputText(InputText const &to_copy) = default;
            InputText(InputText &&to_move) = default;
            InputText &operator=(InputText const &to_copy) = default;
            InputText &operator=(InputText &&to_move) = default;
            std::shared_ptr<sf::RectangleShape> get_shape();
            void draw(sf::RenderWindow &window);
            void start_input();
            void end_input();
            std::string get_input();
            void set_input(char input);
            bool is_clicked() const;
            void pop_input();
        private:
            std::shared_ptr<sf::RectangleShape> shape_;
            std::string input_;
            std::string font_path_;
            sf::Vector2f position_text_;
            bool is_clicked_{false};
    };
}
