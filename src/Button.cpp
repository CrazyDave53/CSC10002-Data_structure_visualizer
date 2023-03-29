#include "Button.h"
#include <iostream>

Button::Button() :
    normalTexture_(),
    hoverTexture_(),
    normalSprite_(),
    hoverSprite_(),
    position_(),
    isHovered_(false),
    isToggled_(false),
    Toggled_(false)
{

}

Button::Button(std::string name, sf::Vector2f center, bool Toggled = false) :
    normalTexture_(),
    hoverTexture_(),
    normalSprite_(),
    hoverSprite_(),
    position_(),
    isHovered_(false),
    isToggled_(false),
    Toggled_(Toggled)
{
    std::string normalTextureFile = "./assets/button/" + name + "_normal.png";
    std::string hoverTextureFile = "./assets/button/" + name + "_hover.png";

    normalTexture_.loadFromFile(normalTextureFile);
    hoverTexture_.loadFromFile(hoverTextureFile);

    normalSprite_.setTexture(normalTexture_);
    hoverSprite_.setTexture(hoverTexture_);

    position_ = center - normalSprite_.getScale() * 0.5f;

    normalSprite_.setOrigin(normalSprite_.getGlobalBounds().width / 2.f, normalSprite_.getGlobalBounds().height / 2.f);
    hoverSprite_.setOrigin(hoverSprite_.getGlobalBounds().width / 2.f, hoverSprite_.getGlobalBounds().height / 2.f);

    normalSprite_.setPosition(position_);
    hoverSprite_.setPosition(position_);
}

void Button::draw(sf::RenderWindow& window) {
    if (isToggled_) {
        window.draw(hoverSprite_);
        return;
    }

    window.draw(isHovered_ ? hoverSprite_ : normalSprite_);
}

bool Button::contains(sf::Vector2i point) {
    return normalSprite_.getGlobalBounds().contains(static_cast<sf::Vector2f>(point));
}

bool Button::isClicked(sf::RenderWindow& window) {
    bool clicked = contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if(clicked)
        setToggled(!isToggled_);
    return clicked;
}

bool Button::setHovered(sf::RenderWindow& window) {
    bool hovered = contains(sf::Mouse::getPosition(window));
    bool diff = (isHovered_ ^ hovered);
    isHovered_ = hovered;

    return diff;
}

void Button::setToggled(bool toggled) {
    if(Toggled_)
        isToggled_ = toggled;
}

bool Button::isToggled() {
    return isToggled_;
}

sf::FloatRect Button::getGlobalBounds() {
    return normalSprite_.getGlobalBounds();
}
