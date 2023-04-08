#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_MAINMENU_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_MAINMENU_H

#include "../Gui/Theme.hpp"
#include "../Gui/Gui.hpp"
#include <SFML/Graphics.hpp>
#include "windowsList.h"
#include "iostream"

class mainMenu{
public:
    mainMenu(sf::RenderWindow& window);
    windowType mainloop(sf::RenderWindow& window);
private:
    gui::Menu menu;
    sf::Texture buttonBG;
    gui::SpriteButton *playButton;
    gui::SpriteButton *exitButton;
    windowType nextWindow;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_DISPLAYWINDOW_H


