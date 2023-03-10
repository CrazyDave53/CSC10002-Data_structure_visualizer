#include "Button.h"

Button::Button() {
    sf::Font f;
    f.loadFromFile("./fonts/ARLRDBD.TTF");
    ButtonCornerRadius = 1;
//    Button(sf::Vector2f(960, 540), sf::Vector2f(400, 60), "Play me m", f, sf::Color::White, sf::Color::Black, 26, 1.0);
}

Button::Button(sf::Vector2f _centre, sf::Vector2f size, std::string text, sf::Font font, sf::Color backgroundColor,
               sf::Color textColor, int textSize, float cornerRadius) {
    pos = centre - size * 0.5f;

    ButtonShape.setPosition(pos);
    ButtonShape.setSize(size);
    ButtonShape.setFillColor(backgroundColor);

    ButtonShape.setOutlineThickness(cornerRadius);
    ButtonShape.setOutlineColor(backgroundColor);
//    ButtonShape.setCon(8);
    ButtonCornerRadius = cornerRadius;

    ButtonText.setString(text);
    ButtonText.setFont(font);
    ButtonText.setCharacterSize(textSize);
    ButtonText.setFillColor(textColor);


    sf::FloatRect textBounds = ButtonText.getLocalBounds();
    ButtonText.setPosition(pos + size / 2.f - sf::Vector2f(textBounds.width / 2.f, textBounds.height / 2.f));
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) {
    target.draw(ButtonShape, states);
    target.draw(ButtonText, states);
}