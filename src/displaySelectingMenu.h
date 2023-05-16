#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_DISPLAYSELECTINGMENU_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_DISPLAYSELECTINGMENU_H

#include "../Gui/Theme.hpp"
#include "../Gui/Gui.hpp"
#include <SFML/Graphics.hpp>
#include "windowsList.h"
#include "popUpMenu.h"
#include "node.h"
#include "iostream"
#include "background.h"
#include "mediaBar.h"

class displaySelectingMenu{
public:
    displaySelectingMenu(sf::RenderWindow& window);
    ~displaySelectingMenu();
    windowType mainloop(sf::RenderWindow& window);
private:
    gui::Menu menu;

    gui::HBoxLayout* layout1;
    gui::HBoxLayout* layout2;

    windowType nextWindow;

    sf::Texture linkedListTexture;
    sf::Texture doublyLinkedListTexture;
    sf::Texture circularLinkedListTexture;
    sf::Texture stackTexture;
    sf::Texture queueTexture;
    sf::Texture staticArrayTexture;
    sf::Texture dynamicArrayTexture;

    gui::SpriteButton* linkedList;
    gui::SpriteButton* doublyLinkedList;
    gui::SpriteButton* circularLinkedList;
    gui::SpriteButton* stack;
    gui::SpriteButton* queue;
    gui::SpriteButton* staticArray;
    gui::SpriteButton* dynamicArray;

    sf::Texture TitleTexture;
    sf::Sprite TitleSprite;

    backGround bg;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_DISPLAYSELECTINGMENU_H
