#include "node.h"

node::node(int number, float x, float y):
osuCircle(),
highlightCircle(),
circle(),
inPivot(),
outPivot(),
next(),
number(number),
numText(number,sf::Vector2f(x,y)),
arrow(inPivot,outPivot),
font(),
highlighted()
{
    pos.x = x;
    pos.y = y;
    startingPoint = pos;
    endingPoint = pos;

    osuCircle.loadFromFile("./assets/textures/circle.png");
    highlightCircle.loadFromFile("./assets/textures/circleHighlighted.png");
    circle.setTexture(osuCircle);
    circle.setOrigin(circle.getGlobalBounds().width/2, circle.getGlobalBounds().height/2);
    circle.setPosition(x, y);
    numText.update(pos);

    update();
}

void node::update() {
    updatePos();
    if(highlighted){
        circle.setTexture(highlightCircle);
    }
    else
        circle.setTexture(osuCircle);
    circle.setPosition(pos);
    numText.update(pos);


    inPivot.x = circle.getGlobalBounds().left;
    inPivot.y = circle.getGlobalBounds().top + circle.getGlobalBounds().height/2.0f;

    outPivot.x = circle.getGlobalBounds().left + circle.getGlobalBounds().width;
    outPivot.y = circle.getGlobalBounds().top + circle.getGlobalBounds().height/2.0f;

    if(next != nullptr){
        arrow.setStart(outPivot);
        arrow.setEnd(next->inPivot);
        arrow.setThickness(5);
//        arrow.setArrowSize(7);
        arrow.update();
    }
}

void node::draw(sf::RenderWindow &window) {
    update();
    window.draw(circle);
    numText.draw(window);
    if(next != nullptr){
        arrow.update();
        arrow.draw(window);
    }
}

void node::setHighlight(bool isHiglighted) {
    highlighted = isHiglighted;
}


