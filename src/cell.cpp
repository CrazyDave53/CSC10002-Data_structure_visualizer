#include "cell.h"

Cell::Cell() :
    Cell(0, 0, sf::Vector2f(-100, -100))
{

}

Cell::Cell(int value, int index, sf::Vector2f center, bool _isNull) :
    movable(),
    transition(),
    value(value),
    index(index),
    isNull(_isNull),
    numText(value, center),
    indexText(index, center - sf::Vector2f(0, 100)),
    isHighlighted(false),
    state(normalSquareState),
    phase(0)
{
    outlineSquare.loadFromFile("./assets/textures/outline-square.png");
    highlightSquare.loadFromFile("./assets/textures/highlight-square.png");
    greenSquareTexture.loadFromFile("./assets/textures/green-square.png");
    redSquareTexture.loadFromFile("./assets/textures/red-square.png");
    nullTexture.loadFromFile("./assets/textures/null.png");

    square.setTexture(outlineSquare);
    square.setOrigin(sf::Vector2f(outlineSquare.getSize().x / 2, outlineSquare.getSize().y / 2));
    square.setPosition(center);

    fadingSquare.setTexture(outlineSquare);
    fadingSquare.setOrigin(sf::Vector2f(outlineSquare.getSize().x / 2, outlineSquare.getSize().y / 2));
    fadingSquare.setPosition(center);

    null.setTexture(nullTexture);
    null.setOrigin(sf::Vector2f(nullTexture.getSize().x / 2, nullTexture.getSize().y / 2));
    null.setPosition(center);

    numText.pos = center;
    indexText.pos = center - sf::Vector2f(0, 100);



    numText.update();
    indexText.update();
}

Cell::~Cell() {

}

void Cell::loadTexture() {
    outlineSquare.loadFromFile("./assets/textures/outline-square.png");
    highlightSquare.loadFromFile("./assets/textures/highlight-square.png");
    nullTexture.loadFromFile("./assets/textures/null.png");

    square.setTexture(outlineSquare);
    fadingSquare.setTexture(outlineSquare);
    null.setTexture(nullTexture);

    numText.loadTexture();
    indexText.loadTexture();
}

void Cell::setValue(int _value) {
    value = _value;
    numText.number = value;
    update();
}

int Cell::getValue() {
    return value;
}

void Cell::setIndex(int index) {
    this->index = index;
    indexText.number = index;
    update();
}

int Cell::getIndex() {
    return index;
}

void Cell::update() {
    updateFading();
    updatePos();
    square.setPosition(pos);
    fadingSquare.setPosition(pos);
    null.setPosition(pos);
    if(!numText.isMoving)
        numText.update(pos);
    else
        numText.update();
    indexText.update(pos - sf::Vector2f(0, 100));
}

void Cell::draw(sf::RenderWindow& window) {
    update();
    if (isFading) {
        window.draw(fadingSquare);
    }
    window.draw(square);
    if(isNull){
        window.draw(null);
    }
    else{
        numText.draw(window);
    }
    indexText.draw(window);
}

void Cell::setHighlighted(bool _isHighlighted) {
    isHighlighted = _isHighlighted;
    update();
}

void Cell::setNull(bool _isNull) {
    isNull = _isNull;
}

void Cell::updateFading() {
    updateOpacity();
    square.setColor(sf::Color(255, 255, 255, 255));
    if(isFading){
        fadingSquare.setColor(sf::Color(255, 255, 255, opacity));
        square.setColor(sf::Color(255, 255, 255, 255 - opacity));
    }
}

void Cell::setState(squareState newState, float duration) {
    startFading(duration);

    switch (state) {
        case normalSquareState:
            fadingSquare.setTexture(outlineSquare);
            break;
        case highlightedSquareState:
            fadingSquare.setTexture(highlightSquare);
            break;
        case greenSquareState:
            fadingSquare.setTexture(greenSquareTexture);
            break;
        case redSquareState:
            fadingSquare.setTexture(redSquareTexture);
            break;

    }

    switch (newState) {
        case normalSquareState:
            square.setTexture(outlineSquare);
            break;
        case highlightedSquareState:
            square.setTexture(highlightSquare);
            break;
        case greenSquareState:
            square.setTexture(greenSquareTexture);
            break;
        case redSquareState:
            square.setTexture(redSquareTexture);
            break;
    }
    state = newState;
    updateFading();
}

void Cell::setStateImmediately(squareState newState) {
    startFading(100);

    switch (state) {
        case normalSquareState:
            fadingSquare.setTexture(outlineSquare);
            break;
        case highlightedSquareState:
            fadingSquare.setTexture(highlightSquare);
            break;
        case greenSquareState:
            fadingSquare.setTexture(greenSquareTexture);
            break;
        case redSquareState:
            fadingSquare.setTexture(redSquareTexture);
            break;

    }

    switch (newState) {
        case normalSquareState:
            square.setTexture(outlineSquare);
            break;
        case highlightedSquareState:
            square.setTexture(highlightSquare);
            break;
        case greenSquareState:
            square.setTexture(greenSquareTexture);
            break;
        case redSquareState:
            square.setTexture(redSquareTexture);
            break;
    }

    state = newState;
    opacity = 0;
    updateOpacity();
}


