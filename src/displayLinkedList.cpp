#include "displayLinkedList.h"
#include <iostream>
#include <string>
displayLinkedList::displayLinkedList(sf::RenderWindow &window):
    menu(window),
    nextWindow(singlyLinkedListWindow),
    createMenu(menu, "Create"),
    searchMenu(menu, "Search"),
    createRandom(),
    buttonBG(),
    linkedList()
{
    menu.setPosition(100,600);
    buttonBG.loadFromFile("./assets/button/button.png");
    createMenu.mainButton->setCallback([this]{
        createMenu.deleteFrame();
        createMenu.frame = createMenu.mainframe->addHBoxLayout();
        createRandom = new gui::SpriteButton(buttonBG,"Random");
        createMenu.frame->add(createRandom);
        createRandom->setCallback([this]{
//            createMenu.deleteFrame();
//            createMenu.frame = createMenu.mainframe->addHBoxLayout();
            inputSize = new gui::TextBox(100);
            goCreateRandom = new::gui::SpriteButton(buttonBG,"GO");
            createMenu.frame->add(inputSize);
            createMenu.frame->add(goCreateRandom);
            goCreateRandom->setCallback([this]{
                linkedList.createRandom(std::stoi(inputSize->getText().toAnsiString()));
            });
        });
    });
}

windowType displayLinkedList::mainloop(sf::RenderWindow &window) {
    nextWindow = singlyLinkedListWindow;
    while (window.isOpen() && nextWindow == singlyLinkedListWindow)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Send events to menu
            menu.onEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
//        std::cout << createMenu.frame << "\n";
        // Clear screen
        if(!createMenu.mainframe->isFocused()){
            createMenu.deleteFrame();
        }
        window.clear(gui::Theme::windowBgColor);

        linkedList.draw(window);
        window.draw(menu);
        // Update the window
        window.display();
    }
    return nextWindow;
}
