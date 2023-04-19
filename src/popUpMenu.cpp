#include "popUpMenu.h"

popUpMenu::popUpMenu(gui::Menu &menu, std::string _name) :
    mainframe(),
    frame(),
    mainButton(),
    buttonBG(),
    name(_name)
{
    mainframe = menu.addHBoxLayout();
    buttonBG.loadFromFile("./assets/button/newbutton.png");
    mainButton = new gui::SpriteButton(buttonBG, name);
    mainframe->add(mainButton);
}

void popUpMenu::deleteFrame() {
    if(frame != nullptr){
        mainframe->removeLast();
        frame = nullptr;
    }
}

void popUpMenu::setPosition(float x, float y) {
    mainframe->setPosition(x, y);
}
