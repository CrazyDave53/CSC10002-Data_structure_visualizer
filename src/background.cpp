#include "background.h"

backGround::backGround() :
    bgimg(),
    bg()
{
    bgimg.loadFromFile("./assets/textures/BG-skylight.png");
    bg.setTexture(bgimg);
}

void backGround::draw(sf::RenderWindow &window) {
    window.draw(bg);
}
