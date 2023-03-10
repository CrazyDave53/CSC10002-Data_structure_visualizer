#include "render.h"

void Application::changeWindowtype(int type) {
    windowType = type;
}

void Application::initWindow() {
    window.create(sf::VideoMode(1920,1080), "DSA Visualizer");
    window.setPosition(sf::Vector2i(0,0));
}

void Application::renderWindow() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        switch (windowType)
            case mainMenu:

                break;
    }
}