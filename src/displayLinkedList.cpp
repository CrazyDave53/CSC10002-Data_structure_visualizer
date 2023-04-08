#include "displayLinkedList.h"

displayLinkedList::displayLinkedList(sf::RenderWindow &window):
    menu(window),
    nextWindow(singlyLinkedListWindow),
    createMenu(menu, "Create"),
    searchMenu(menu, "Search")
{
    createMenu.setPosition(100,100);
    searchMenu.setPosition(200,200);
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

        // Clear screen
        window.clear(gui::Theme::windowBgColor);
        window.draw(menu);
        // Update the window
        window.display();
    }
    return nextWindow;

}
