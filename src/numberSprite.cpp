#include "numberSprite.h"

numberSprite::numberSprite(int number, sf::Vector2f center):
    number(number)
{
    if (number < 0 || number > 99) {
        throw std::invalid_argument("Invalid number (must be between 0 and 99)");
    }

    // Load digit images
    for (int i = 0; i < 10; i++) {
        m_digitTextures[i].loadFromFile("./assets/textures/score-" + std::to_string(i) + ".png");
        m_digitSprites[i].setTexture(m_digitTextures[i]);
        m_digitSprites[i+10].setTexture(m_digitTextures[i]);
    }

    // Calculate digit positions based on number of digits
    sf::Vector2f digitSize(m_digitTextures[0].getSize());
    if (number < 10) {
        m_digitSprites[number].setPosition(center - sf::Vector2f(digitSize.x / 2, digitSize.y / 2));
    } else {
        tens = number / 10;
        ones = number % 10;
        m_digitSprites[tens+10].setPosition(center - sf::Vector2f(digitSize.x, digitSize.y / 2));
        m_digitSprites[ones].setPosition(center + sf::Vector2f(0, -digitSize.y / 2));
    }
}

void numberSprite::draw(sf::RenderWindow &window) {
    if(number<10){
        window.draw(m_digitSprites[number]);
    }
    else{
        window.draw(m_digitSprites[tens+10]);
        window.draw(m_digitSprites[ones]);
    }
}

void numberSprite::update(sf::Vector2f center) {
    sf::Vector2f digitSize(m_digitTextures[0].getSize());
    if (number < 10) {
        m_digitSprites[number].setPosition(center - sf::Vector2f(digitSize.x / 2, digitSize.y / 2));
    } else {
        tens = number / 10;
        ones = number % 10;
        m_digitSprites[tens+10].setPosition(center - sf::Vector2f(digitSize.x, digitSize.y / 2));
        m_digitSprites[ones].setPosition(center + sf::Vector2f(0, -digitSize.y / 2));
    }
}

void numberSprite::setOpacity(float opacity) {
    if (number < 10){
        m_digitSprites[number].setColor(sf::Color(255, 255, 255, opacity));
    }
    else{
        m_digitSprites[tens+10].setColor(sf::Color(255, 255, 255, opacity));
        m_digitSprites[ones].setColor(sf::Color(255, 255, 255, opacity));
    }
}


