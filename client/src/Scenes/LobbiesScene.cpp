#include "../../include/LobbiesScene.hh"

client::LobbiesScene::LobbiesScene(client::Scene_name scene_name)
{
    this->scene_name_ = scene_name;
    std::string tmp_b = "assets/lobbies/lobbies_bg.png";
    Background tmp_background(sf::Vector2f(0, 0), tmp_b);
    this->background_ = tmp_background;
    std::string tmp_e_but = "assets/lobbies/escape_button.png";
    Button tmp_e_button(sf::Vector2f(1182, 270), sf::Vector2f(31, 31), tmp_e_but);
    this->escape_button_ = std::make_shared<Button>(tmp_e_button);
    std::string tmp_a_but = "assets/lobbies/accept_button.png";
    Button tmp_a_button(sf::Vector2f(963, 720), sf::Vector2f(156, 50), tmp_a_but);
    this->accept_button_ = std::make_shared<Button>(tmp_a_button);
    std::string tmp_r_but = "assets/lobbies/return_button.png";
    Button tmp_r_button(sf::Vector2f(803, 720), sf::Vector2f(156, 50), tmp_r_but);
    this->return_button_ = std::make_shared<Button>(tmp_r_button);
    std::string font = "assets/font/nasalization-rg.ttf";
    //std::string font = "assets/font/arial.ttf";
    InputText tmp_pa_input(sf::Vector2f(718, 338), sf::Vector2f(237, 48), font);
    this->path_input_ = std::make_shared<InputText>(tmp_pa_input);
    InputText tmp_po_input(sf::Vector2f(961, 338), sf::Vector2f(237, 48), font);
    this->port_input_ = std::make_shared<InputText>(tmp_po_input);
}

void client::LobbiesScene::draw(sf::RenderWindow &window)
{
    this->background_.draw(window);
    this->accept_button_->draw(window);
    this->return_button_->draw(window);
    this->escape_button_->draw(window);
    this->path_input_->draw(window);
    this->port_input_->draw(window);
}

bool client::LobbiesScene::is_in_shape(sf::Event::MouseButtonEvent &mouse, sf::RectangleShape &my_shape)
{
    int min_x = my_shape.getPosition().x;
    int min_y = my_shape.getPosition().y;
    int max_x = my_shape.getSize().x + min_x;
    int max_y = my_shape.getSize().y + min_y;

    return min_x < mouse.x && mouse.x < max_x && min_y < mouse.y && mouse.y < max_y;
}

int client::LobbiesScene::poll_event(sf::RenderWindow &window)
{
    while (window.pollEvent(this->event_)) {
        if ((this->event_.type == sf::Event::Closed) ||
        (this->event_.type == sf::Event::KeyPressed &&
        this->event_.key.code == sf::Keyboard::Escape)){
            // open pop up to ask if user wants to quit if he is in a lobby
            window.close();
        }

        // get text from input slot
        if (this->event_.type == sf::Event::TextEntered && this->event_.text.unicode < 128) {
            if (this->path_input_->is_clicked() && !this->port_input_->is_clicked()) {
                if (this->event_.text.unicode == 8) { // 8 = Backspace
                    this->nt_path_.pop_back();
                    this->path_input_->pop_input();
                    continue;
                }
                if (this->event_.text.unicode != 13) { // 13 = Enter
                    this->nt_path_ += static_cast<char>(this->event_.text.unicode);
                    this->path_input_->set_input(static_cast<char>(this->event_.text.unicode));
                } else {
                    this->path_input_->end_input();
                }
            }
            if (this->port_input_->is_clicked() && !this->path_input_->is_clicked()) {
                if (this->event_.text.unicode == 8) { // 8 = Backspace
                    this->nt_port_.pop_back();
                    this->port_input_->pop_input();
                    continue;
                }
                if (this->event_.text.unicode != 13) { // 13 = Enter
                    this->nt_port_ += static_cast<char>(this->event_.text.unicode);
                    this->port_input_->set_input(static_cast<char>(this->event_.text.unicode));
                } else {
                    this->port_input_->end_input();
                }
            }
        }

        // get mouse event
        if ((this->event_.type == sf::Event::MouseButtonPressed) ||
        (this->event_.type == sf::Event::MouseButtonReleased)) {
            // Button click
            if (this->is_in_shape(this->event_.mouseButton, *this->escape_button_->get_shape())) {
                if (this->event_.type == sf::Event::MouseButtonReleased) {
                    this->escape_button_->is_release();
                    // open pop up to ask if user wants to quit if he is in a lobby
                    window.close();
                }
                this->escape_button_->is_clicked();
            }
            if (this->is_in_shape(this->event_.mouseButton, *this->return_button_->get_shape())) {
                if (this->event_.type == sf::Event::MouseButtonReleased) {
                    this->return_button_->is_release();
                    return 1;
                }
                this->return_button_->is_clicked();
            }
            if (this->is_in_shape(this->event_.mouseButton, *this->accept_button_->get_shape())) {
                if (this->event_.type == sf::Event::MouseButtonReleased) {
                    this->accept_button_->is_release();
                    std::cout << this->nt_path_ << "-" << this->nt_port_ << std::endl;
                }
                this->accept_button_->is_clicked();
            }

            // input slot click
            if (this->is_in_shape(this->event_.mouseButton, *this->path_input_->get_shape())) {
                if (this->port_input_->is_clicked()) {
                    this->port_input_->end_input();
                }
                this->path_input_->start_input();
            }
            if (this->is_in_shape(this->event_.mouseButton, *this->port_input_->get_shape())) {
                if (this->path_input_->is_clicked()) {
                    this->path_input_->end_input();
                }
                this->port_input_->start_input();
            }
        }
    }
    return 0;
}