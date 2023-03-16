#include "render.h"

Application::Application() :
    mainMenu()
{
    window.create(sf::VideoMode(1920,1080), "DSA Visualizer");
    window.clear(sf::Color::Black);
    window.setPosition(sf::Vector2i(0,0));
}

void Application::changeWindowtype(int type) {
    windowType = type;
}

void Application::renderWindow() {
    windowType = mainMenuType;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        switch (windowType) {
            case mainMenuType:
                mainMenu.render(window);
                break;
        }


        window.display();
    }
}