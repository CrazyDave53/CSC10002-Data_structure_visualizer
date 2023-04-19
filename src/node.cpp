#include "node.h"

node::node(int number, float x, float y):
    osuCircle(),
    highlightCircle(),
    greenCircle(),
    redCircle(),
    circle(),
    inPivot(),
    outPivot(),
    next(),
    number(number),
    numText(number,sf::Vector2f(x,y)),
    arrow(inPivot,outPivot),
    font(),
    state(),
    phase()
{
    pos.x = x;
    pos.y = y;
    startingPoint = pos;
    endingPoint = pos;

    osuCircle.loadFromFile("./assets/textures/circle.png");
    highlightCircle.loadFromFile("./assets/textures/circleHighlighted.png");
    greenCircle.loadFromFile("./assets/textures/circleHighlighted2.png");
    redCircle.loadFromFile("./assets/textures/circleHighlighted3.png");
    circle.setTexture(osuCircle);
    circle.setOrigin(circle.getGlobalBounds().width/2, circle.getGlobalBounds().height/2);
    circle.setPosition(x, y);

    fadingCircle.setTexture(osuCircle);
    fadingCircle.setOrigin(fadingCircle.getGlobalBounds().width/2, fadingCircle.getGlobalBounds().height/2);
    fadingCircle.setPosition(x, y);

    numText.update(pos);

    update();
}

void node::update() {
    updatePos();
    updateFading();

    circle.setPosition(pos);
    fadingCircle.setPosition(pos);
    numText.update(pos);
    updateArrow();
}

void node::updateArrow() {
    inPivot.x = circle.getGlobalBounds().left;
    inPivot.y = circle.getGlobalBounds().top + circle.getGlobalBounds().height/2.0f;

    outPivot.x = circle.getGlobalBounds().left + circle.getGlobalBounds().width;
    outPivot.y = circle.getGlobalBounds().top + circle.getGlobalBounds().height/2.0f;

    if(next != nullptr){
        float distance = sqrt(pow(next->pos.x - pos.x, 2) + pow(next->pos.y - pos.y, 2));
        outPivot = (next->pos - pos)/(distance)*circle.getGlobalBounds().width/2.0f + pos;
        next->inPivot = (pos - next->pos)/(distance)*circle.getGlobalBounds().width/2.0f + next->pos;
        arrow.setStart(outPivot);
        arrow.setEnd(next->inPivot);
        arrow.setThickness(5);
//        arrow.setArrowSize(7);
        arrow.update();
    }
}



void node::draw(sf::RenderWindow &window) {
    update();
    window.draw(fadingCircle);
    window.draw(circle);
    numText.draw(window);
    if(next != nullptr){
        arrow.update();
        arrow.draw(window);
    }
}


void node::updateFading() {
    updateOpacity();
    if(!isFading && !isAppearing)
        return;
    sf::Color fading = fadingCircle.getColor();
    fading.a = opacity;
    fadingCircle.setColor(fading);
    if(isFading){
        sf::Color appearing = circle.getColor();
        appearing.a = 255-opacity;
        circle.setColor(appearing);
    }
}

void node::setState(circleState newState, float duration) {
    startFading(duration);
    switch(state){
        case normal:
            fadingCircle.setTexture(osuCircle);
            break;
        case highlighted:
            fadingCircle.setTexture(highlightCircle);
            break;
        case green:
            fadingCircle.setTexture(greenCircle);
            break;
        case red:
            fadingCircle.setTexture(redCircle);
            break;
    }
    switch(newState){
        case normal:
            circle.setTexture(osuCircle);
            break;
        case highlighted:
            circle.setTexture(highlightCircle);
            break;
        case green:
            circle.setTexture(greenCircle);
            break;
        case red:
            circle.setTexture(redCircle);
            break;
    }
    state = newState;
    updateFading();
}

void node::appear() {
    startAppearing(500.0f);
    circle.setTexture(osuCircle);
    fadingCircle.setTexture(osuCircle);
    updateOpacity();
}


