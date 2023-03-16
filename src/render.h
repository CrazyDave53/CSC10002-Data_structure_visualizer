#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_RENDER_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_RENDER_H

#define mainMenuType 0
#define selectingType 1

#include <string>
#include <SFML/Graphics.hpp>
#include "menu.h"

class Application{
public:
    Application();
    void changeWindowtype(int type);
    void renderWindow();
private:
    int windowType = 0;
    sf::RenderWindow window;
    menu mainMenu;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_RENDER_H