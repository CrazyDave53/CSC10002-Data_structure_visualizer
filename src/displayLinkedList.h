#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_DISPLAYLINKEDLIST_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_DISPLAYLINKEDLIST_H

#include "../Gui/Theme.hpp"
#include "../Gui/Gui.hpp"
#include <SFML/Graphics.hpp>
#include "windowsList.h"
#include "popUpMenu.h"
#include "iostream"

class displayLinkedList{
public:
    displayLinkedList(sf::RenderWindow& window);
    windowType mainloop(sf::RenderWindow& window);
private:
    gui::Menu menu;
    windowType nextWindow;
    popUpMenu createMenu;
    popUpMenu searchMenu;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_DISPLAYLINKEDLIST_H
