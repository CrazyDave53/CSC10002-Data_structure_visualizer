#include "mainMenu.h"

mainMenu::mainMenu(sf::RenderWindow &window) :
    menu(window),
    playBG(),
    exitBG(),
    playButton(),
    exitButton(),
    nextWindow(mainMenuWindow),
    bg()
{
    menu.setPosition(0,0);

    playBG.loadFromFile("./assets/button/menuPlay.png");
    exitBG.loadFromFile("./assets/button/menuExit.png");
    playButton = new gui::SpriteButton(playBG);
    exitButton = new gui::SpriteButton(exitBG);

    playButton->setCallback([&](){
        nextWindow = selectingMenuWindow;
    });

    exitButton->setCallback([&](){
        window.close();
    });

    menu.add(playButton);
    menu.add(exitButton);

    sf::Vector2f size;
    size = playButton->getSize();
    playButton->setPosition(1920/2 - size.x/2,1080/2 - size.y/2);
    exitButton->setPosition(1920/2 - size.x/2,1080/2 - size.y/2 + 300);

    TitleTexture.loadFromFile("./assets/textures/Title.png");
    TitleSprite.setTexture(TitleTexture);
    TitleSprite.setOrigin(TitleTexture.getSize().x/2, TitleTexture.getSize().y/2);
    TitleSprite.setPosition(1920/2, 200);
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
        bg.draw(window);
        window.draw(menu);
        window.draw(TitleSprite);
        // Update the window
        window.display();
    }
    return nextWindow;
}

