//
// Created by Xavier VINCENT on 14/12/2023.
//

/*#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        // Draw your SFML content here
        window.display();
    }

    return 0;
}
*/

#include "Network.hpp"

int main()
{
    boost::asio::io_context io;
    Client::Network network(io, DEFAULT_IP, DEFAULT_PORT);

    io.run();

    network.connect_to_server();
    network.send_name("John Doe");
    network.join_room(0);
}
