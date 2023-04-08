#include "mainMenu.h"

mainMenu::mainMenu(sf::RenderWindow &window) :
    menu(window),
    buttonBG(),
    playButton(),
    exitButton(),
    nextWindow(mainMenuWindow)
{
    menu.setPosition(0,0);

    buttonBG.loadFromFile("./assets/textures/themed-button.png");
    playButton = new gui::SpriteButton(buttonBG,"Play");
    exitButton = new gui::SpriteButton(buttonBG,"Exit");

    playButton->setCallback([&](){
        nextWindow = singlyLinkedListWindow;
    });

    exitButton->setCallback([&](){
        window.close();
    });

    menu.add(playButton);
    menu.add(exitButton);

    sf::Vector2f size;
    size = playButton->getSize();
    playButton->setPosition(1920/2 - size.x/2,1080/2 - size.y/2);
    exitButton->setPosition(1920/2 - size.x/2,1080/2 - size.y/2 + 200);
}

windowType mainMenu::mainloop(sf::RenderWindow &window) {
    nextWindow = mainMenuWindow;
    while (window.isOpen() && nextWindow == mainMenuWindow)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Send events to menu
            menu.onEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear(gui::Theme::windowBgColor);
        window.draw(menu);
        // Update the window
        window.display();
    }
    return nextWindow;
}

