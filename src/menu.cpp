#include "menu.h"
#include <iostream>

menu::menu() :
    mainButton("mainLogo", sf::Vector2f(540,540), true),
    playButton("menuPlay", sf::Vector2f(400,400), true),
    settingButton("button", sf::Vector2f(800,800), true),
    quitButton("button", sf::Vector2f(1000,800), true)
    {}

void menu::render(sf::RenderWindow &window, int &windowType) {
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

        mainButton.draw(window);
        playButton.draw(window);
        settingButton.draw(window);
        quitButton.draw(window);

        window.display();
    }
}

