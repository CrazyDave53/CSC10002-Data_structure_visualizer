#include "menu.h"
#include <iostream>

menu::menu() :
    playButton("button", sf::Vector2f(400,400), true),
    settingButton("button", sf::Vector2f(800,800), true),
    quitButton("button", sf::Vector2f(1000,800), true)
{

}

void menu::render(sf::RenderWindow &window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseMoved) {
                playButton.setHovered(window);
                settingButton.setHovered(window);
                quitButton.setHovered(window);
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                playButton.isClicked(window);
                settingButton.isClicked(window);
                quitButton.isClicked(window);
            }
        }

        window.clear();

        playButton.draw(window);
        settingButton.draw(window);
        quitButton.draw(window);

        window.display();
    }
}

