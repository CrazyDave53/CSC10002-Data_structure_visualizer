#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_MENU_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_MENU_H

#include <SFML/Graphics.hpp>
#include "Button.h"

class MainMenu {
private:
    sf::Font ButtonFont = sf::Font();
    Button PlayButton = Button();
    Button SettingButton = Button();
public:
    MainMenu();
    void draw(sf::RenderTarget &target, sf::RenderStates states);
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_MENU_H
