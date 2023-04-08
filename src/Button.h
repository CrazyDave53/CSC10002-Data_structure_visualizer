#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_BUTTON_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

class Button {
public:
    Button();

    Button(std::string name, sf::Vector2f center, bool Toggled);

    void draw(sf::RenderWindow& window);

    bool contains(sf::Vector2i point);

    bool isClicked(sf::RenderWindow& window);

    bool setHovered(sf::RenderWindow& window);

    void setToggled(bool toggled);

    bool isToggled();

    sf::FloatRect getGlobalBounds();

    void setCallback(std::function<void(void)> callback);

    void triggerCallback();

private:
    sf::Texture normalTexture_;
    sf::Texture hoverTexture_;
    sf::Sprite normalSprite_;
    sf::Sprite hoverSprite_;
    sf::Vector2f position_;
    bool isHovered_;
    bool isToggled_;
    bool Toggled_;
    std::string name_;
    std::function<void(void)> callback_;
};

#endif