#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/System/Vector2.hpp>
#include "model/headers/Board.h"
#include "model/FontLoader.h"
static constexpr int FRAMERATE_LIMIT = 60;

//TODO screensaver bevegelse på fysisk vindu
//utvidelse i bredde og høydre randomly
//cooldown på brikker
int main() {

    sf::ContextSettings settings;



    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Sjakkalaka", sf::Style::Default, settings);
    window.setFramerateLimit(FRAMERATE_LIMIT);
    window.setPosition(sf::Vector2i(800, 200));


    Board board(1000);
    FontLoader::getInstance().load_font("/Users/Admin/CLionProjects/myFirstGame/include/AovelSansRounded-rdDL.ttf");

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {

            switch (event.type) {
                case sf::Event::MouseButtonPressed:
                    board.on_mouse_clicked(sf::Mouse::getPosition(window));
                break;
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }

        }

        window.draw(board);

        window.display();
    }

    return 0;
}
