#include "numberSprite.h"
#include <iostream>

numberSprite::numberSprite(int inputNumber, sf::Vector2f center):
    number(inputNumber),
    transition(),
    movable(),
    tens(inputNumber / 10),
    ones(inputNumber % 10)
{
    pos = center;
    startingPoint = center;
    endingPoint = center;

    if (inputNumber < 0 || inputNumber > 99) {
        inputNumber = rand() % 100;
        number = inputNumber;
        std::cout << "Invalid number input, random number generated: " << inputNumber << std::endl;
    }
    std::cout << "Invalid number input, random number generated: " << inputNumber << std::endl;
    // Load digit images
    for (int i = 0; i < 10; i++) {
        m_digitTextures[i].loadFromFile("./assets/textures/score-" + std::to_string(i) + ".png");
        m_digitSprites[i].setTexture(m_digitTextures[i]);
        m_digitSprites[i+10].setTexture(m_digitTextures[i]);
    }

    // Calculate digit positions based on number of digits
    sf::Vector2f digitSize(m_digitTextures[0].getSize());
    if (inputNumber < 10) {
        m_digitSprites[inputNumber].setPosition(center - sf::Vector2f(digitSize.x / 2, digitSize.y / 2));
    } else {
        tens = inputNumber / 10;
        ones = inputNumber % 10;
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

void numberSprite::update(){
    updatePos();
    update(pos);
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

void numberSprite::loadTexture() {
    for (int i = 0; i < 10; i++) {
        m_digitTextures[i].loadFromFile("./assets/textures/score-" + std::to_string(i) + ".png");
        m_digitSprites[i].setTexture(m_digitTextures[i]);
        m_digitSprites[i+10].setTexture(m_digitTextures[i]);
    }
}


