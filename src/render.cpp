#include "render.h"

void Application::changeWindowtype(int type) {
    windowType = type;
}

void Application::initWindow() {
    window.create(sf::VideoMode(1920,1080), "DSA Visualizer");
    window.clear(sf::Color::Black);
    window.setPosition(sf::Vector2i(0,0));
}

void Application::renderWindow() {
    windowType = mainMenu;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        switch (windowType) {
            case mainMenu:
                menu.draw(window, sf::RenderStates::Default);
                break;
        }
        window.display();
    }
}