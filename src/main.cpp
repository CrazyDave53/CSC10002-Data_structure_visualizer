#include "mainMenu.h"

#include "displaySelectingMenu.h"
#include "displayLinkedList.h"
#include "displayDoublyLinkedList.h"
#include "displayCircularLinkedList.h"
#include "displayStack.h"
#include "displayQueue.h"
#include "displayStaticArray.h"
#include "displayDynamicArray.h"


int main(){
    srand(time(NULL));
    gui::Theme::loadFont("./assets/textures/tahoma.ttf");
    gui::Theme::loadTexture("./assets/textures/pinky.png");
    gui::Theme::textSize = 20;
    gui::Theme::PADDING = 3.0f;
    gui::Theme::click.textColor = sf::Color(255, 255, 255);
    gui::Theme::input.textColor = sf::Color(255, 255, 255);
    gui::Theme::windowBgColor = sf::Color(0,0,0);
    gui::Theme::minWidgetWidth = 43;
    gui::Theme::input.textPlaceholderColor = sf::Color(252, 156, 178);

    sf::RenderWindow app(sf::VideoMode(1920, 1080), "SFML Widgets", sf::Style::Close);
    app.setFramerateLimit(60);

    mainMenu mainMenu(app);

    displaySelectingMenu displaySelectingMenu(app);

    displayLinkedList displayLinkedList(app);
    displayDoublyLinkedList displayDoublyLinkedList(app);
    displayCircularLinkedList displayCircularLinkedList(app);
    displayQueue displayQueue(app);
    displayStack displayStack(app);
    displayStaticArray displayStaticArray(app);
    displayDynamicArray displayDynamicArray(app);


    windowType nowDisplay;
    nowDisplay = mainMenuWindow;

    while(app.isOpen()){
        switch(nowDisplay){
            case mainMenuWindow:
                nowDisplay = mainMenu.mainloop(app);
                break;
            case selectingMenuWindow:
                nowDisplay = displaySelectingMenu.mainloop(app);
                break;
            case singlyLinkedListWindow:
                nowDisplay = displayLinkedList.mainloop(app);
                break;
            case doublyLinkedListWindow:
                nowDisplay = displayDoublyLinkedList.mainloop(app);
                break;
            case circularLinkedListWindow:
                nowDisplay = displayCircularLinkedList.mainloop(app);
                break;
            case queueWindow:
                nowDisplay = displayQueue.mainloop(app);
                break;
            case stackWindow:
                nowDisplay = displayStack.mainloop(app);
                break;
            case staticArrayWindow:
                nowDisplay = displayStaticArray.mainloop(app);
                break;
            case dynamicArrayWindow:
                nowDisplay = displayDynamicArray.mainloop(app);
                break;
        }
    }
}
