#include "menu.h"

MainMenu::MainMenu() {
    ButtonFont.loadFromFile("./fonts/ARLRDBD.TTF");
    PlayButton = Button(sf::Vector2f(960, 540), sf::Vector2f(400, 60), "Play me m", ButtonFont, sf::Color::White, sf::Color::Black, 26, 1.0);
}

void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) {
    PlayButton.draw(target, states);
}

