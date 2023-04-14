#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_DISPLAYLINKEDLIST_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_DISPLAYLINKEDLIST_H

#include "../Gui/Theme.hpp"
#include "../Gui/Gui.hpp"
#include <SFML/Graphics.hpp>
#include "windowsList.h"
#include "popUpMenu.h"
#include "node.h"
#include "iostream"
#include "linkedList.h"

class displayLinkedList{
public:
    displayLinkedList(sf::RenderWindow& window);
    windowType mainloop(sf::RenderWindow& window);
private:
    gui::Menu menu;
    windowType nextWindow;
    popUpMenu createMenu;
    popUpMenu searchMenu;
    sf::Texture buttonBG;
    gui::SpriteButton* createRandom;
    gui::TextBox* inputSize;
    gui::SpriteButton* goCreateRandom;
    LinkedList linkedList;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_DISPLAYLINKEDLIST_H
