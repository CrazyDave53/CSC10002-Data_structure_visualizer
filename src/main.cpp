#include "mainMenu.h"
#include "displayLinkedList.h"


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
