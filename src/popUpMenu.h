#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_POPUPMENU_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_POPUPMENU_H

#include "../Gui/Theme.hpp"
#include "../Gui/Gui.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class popUpMenu{
public:
    popUpMenu(gui::Menu &menu, std::string _name);
    void setPosition(float x, float y);
    gui::HBoxLayout *mainframe;
    gui::HBoxLayout *frame;
    gui::SpriteButton *mainButton;
    void deleteFrame();
private:
    sf::Texture buttonBG;
    std::string name;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_POPUPMENU_H
