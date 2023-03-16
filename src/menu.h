#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_MENU_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_MENU_H

#include <SFML/Graphics.hpp>
#include "Button.h"

class menu {

public:
    menu();
    void render(sf::RenderWindow& window);
private:
    Button playButton;
    Button settingButton;
    Button quitButton;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_MENU_H
