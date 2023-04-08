#include "mainMenu.h"
#include "displayLinkedList.h"

int main(){
    gui::Theme::loadFont("./assets/textures/tahoma.ttf");
    gui::Theme::textSize = 20;
    gui::Theme::PADDING = 2.f;
    gui::Theme::windowBgColor = sf::Color(255,255,255);

    sf::RenderWindow app(sf::VideoMode(1920, 1080), "SFML Widgets", sf::Style::Close);
    app.setFramerateLimit(60);

    mainMenu mainMenu(app);
    displayLinkedList displayLinkedList(app);

    windowType nowDisplay;
    while(app.isOpen()){
        switch(nowDisplay){
            case mainMenuWindow:
                nowDisplay = mainMenu.mainloop(app);
                break;
            case selectingMenuWindow:
                break;
            case singlyLinkedListWindow:
                nowDisplay = displayLinkedList.mainloop(app);
                break;
        }
    }
}
