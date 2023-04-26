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
#include "background.h"
#include "codeFrame.h"
#include "mediaBar.h"

class displayLinkedList{
public:
    displayLinkedList(sf::RenderWindow& window);
    windowType mainloop(sf::RenderWindow& window);
private:
    gui::Menu menu;
    windowType nextWindow;
    popUpMenu createMenu;
    popUpMenu searchMenu;
    popUpMenu insertMenu;
    popUpMenu deleteMenu;
    sf::Texture buttonBG;

    gui::VBoxLayout* createRandomFrame;
    gui::SpriteButton* createRandom;
    gui::HBoxLayout* createRandomSizeFrame;
    gui::TextBox* inputSizeCreateRandom;
    gui::Button* goCreateRandom;

    gui::TextBox* inputSearchValue;
    gui::Button* goSearch;

    gui::SpriteButton* insertHead;
    gui::SpriteButton* insertTail;
    gui::SpriteButton* insertArbitrary;

    gui::VBoxLayout* insertHeadFrame;
    gui::VBoxLayout* insertTailFrame;
    gui::VBoxLayout* insertArbitraryFrame;

    gui::HBoxLayout* insertFrame;
    gui::TextBox* inputInsertValue;
    gui::TextBox* inputInsertIndex;
    gui::Button* goInsert;

    gui::SpriteButton* deleteHead;
    gui::SpriteButton* deleteTail;
    gui::SpriteButton* deleteArbitrary;

    gui::VBoxLayout* deleteHeadFrame;
    gui::VBoxLayout* deleteTailFrame;
    gui::VBoxLayout* deleteArbitraryFrame;

    gui::HBoxLayout* deleteFrame;
    gui::TextBox* inputDeleteIndex;
    gui::TextBox* inputDeleteValue;
    gui::Button* goDelete;



    LinkedList linkedList;
    backGround bg;
    mediaBar mediaBar;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_DISPLAYLINKEDLIST_H
