#include "popUpMenu.h"

popUpMenu::popUpMenu(gui::Menu &menu, std::string _name) :
    frame(),
    mainButton(),
    buttonBG(),
    name(_name)
{
    frame = menu.addHBoxLayout();

    buttonBG.loadFromFile("./assets/button/button.png");
    mainButton = new gui::SpriteButton(buttonBG, name);

    frame->add(mainButton);
}

void popUpMenu::setPosition(float x, float y) {
    frame->setPosition(x, y);
}
