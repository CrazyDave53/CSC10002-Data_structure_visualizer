#include "node.h"

node::node(int number, float x, float y, bool reversedArrow) :
        osuCircle(),
        highlightCircle(),
        greenCircle(),
        redCircle(),
        circle(),
        fadingCircle(),
        inPivot(),
        outPivot(),
        reversedInPivot(),
        reversedOutPivot(),
        text(),
        next(),
        prev(),
        number(number),
        numText(number,sf::Vector2f(x,y)),
        arrow(inPivot,outPivot),
        arrowReverse(outPivot,inPivot),
        font(),
        state(),
        phase(),
        textString(),
        isDoubly(reversedArrow)
{
    pos.x = x;
    pos.y = y;
    startingPoint = pos;
    endingPoint = pos;

    osuCircle.loadFromFile("./assets/textures/circle.png");
    highlightCircle.loadFromFile("./assets/textures/circleHighlighted.png");
    greenCircle.loadFromFile("./assets/textures/circleHighlighted2.png");
    redCircle.loadFromFile("./assets/textures/circleHighlighted3.png");
    invisibleCircle.loadFromFile("./assets/textures/circleInvisible.png");
    circle.setTexture(osuCircle);
    circle.setOrigin(circle.getGlobalBounds().width/2, circle.getGlobalBounds().height/2);
    circle.setPosition(x, y);

    fadingCircle.setTexture(osuCircle);
    fadingCircle.setOrigin(fadingCircle.getGlobalBounds().width/2, fadingCircle.getGlobalBounds().height/2);
    fadingCircle.setPosition(x, y);

    numText.update(pos);

    font.loadFromFile("./fonts/ARLRDBD.TTF");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    setText("");
    centerText();
    update();
}

node::node(int number, float x, float y) :
   node(number,x,y,false)
{

}


void node::update() {
    updatePos();
    updateFading();
    numText.number = number;

    circle.setPosition(pos);
    fadingCircle.setPosition(pos);
    numText.update(pos);
    centerText();
    updateArrow();
}

void node::updateArrow() {
    if(isDoubly){
        if(prev != nullptr) {
            float distance = sqrt(pow(prev->pos.x - pos.x, 2) + pow(prev->pos.y - pos.y, 2));
            sf::Vector2f inVec = (prev->pos - pos) / (distance) * circle.getGlobalBounds().width / 2.0f;
            rotate(inVec, 15 * M_PI / 180);
            inPivot = inVec + pos;
            rotate(inVec, -30 * M_PI / 180);
            reversedOutPivot = inVec + pos;
            arrowReverse.setStart(reversedOutPivot);
            arrowReverse.setEnd(prev->reversedInPivot);
            arrowReverse.setThickness(5);
            arrowReverse.update();
        }
        if(next != nullptr){
            float distance = sqrt(pow(next->pos.x - pos.x, 2) + pow(next->pos.y - pos.y, 2));
            sf::Vector2f inVec = (next->pos - pos) / (distance) * circle.getGlobalBounds().width / 2.0f;
            rotate(inVec, -15 * M_PI / 180);
            outPivot = inVec + pos;
            rotate(inVec, 30 * M_PI / 180);
            reversedInPivot = inVec + pos;
            arrow.setStart(outPivot);
            arrow.setEnd(next->inPivot);
            arrow.setThickness(5);
            arrow.update();
        }
    } else{
        outPivot.x = circle.getGlobalBounds().left + circle.getGlobalBounds().width;
        outPivot.y = circle.getGlobalBounds().top + circle.getGlobalBounds().height/2.0f;

        if(next != nullptr){
            float distance = sqrt(pow(next->pos.x - pos.x, 2) + pow(next->pos.y - pos.y, 2));
            outPivot = (next->pos - pos)/(distance)*circle.getGlobalBounds().width/2.0f + pos;
            next->inPivot = (pos - next->pos)/(distance)*circle.getGlobalBounds().width/2.0f + next->pos;
            arrow.setStart(outPivot);
            arrow.setEnd(next->inPivot);
            arrow.setThickness(5);
            arrow.update();
        }
    }
}

void node::draw(sf::RenderWindow &window) {
    update();
    if(!isDisappearing)
        window.draw(fadingCircle);
    window.draw(circle);
    numText.draw(window);
    window.draw(text);
    if(next != nullptr){
        arrow.update();
        arrow.draw(window);
    }
    if(isDoubly && prev != nullptr){
        arrowReverse.update();
        arrowReverse.draw(window);
    }
}

void node::updateFading() {
    updateOpacity();
    if(!isFading && !isAppearing && !isDisappearing)
        return;
    if(isDisappearing){
        sf::Color disappearing = circle.getColor();
        disappearing.a = opacity;
        circle.setColor(disappearing);
        return;
    }
    sf::Color fading = fadingCircle.getColor();
    fading.a = opacity;
    fadingCircle.setColor(fading);
    if(isFading){
        sf::Color appearing = circle.getColor();
        appearing.a = 255-opacity;
        circle.setColor(appearing);
    }
    if(state == invisible){
        numText.setOpacity(opacity);
        arrow.setOpacity(opacity);
        arrowReverse.setOpacity(opacity);
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
        case invisible:
            fadingCircle.setTexture(invisibleCircle);
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
        case invisible:
            circle.setTexture(invisibleCircle);
    }
    state = newState;
    updateFading();
}

void node::setStateImmediately(circleState newState) {
    startFading(100);
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
        case invisible:
            fadingCircle.setTexture(invisibleCircle);
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
        case invisible:
            circle.setTexture(invisibleCircle);
    }
    state = newState;
    opacity = 0;
    updateOpacity();
}

void node::appear() {
    startAppearing(500.0f);
    circle.setTexture(osuCircle);
    fadingCircle.setTexture(osuCircle);
    updateOpacity();
}

void node::setText(const std::string& newString) {
    text.setString(newString);
    textString = newString;
    centerText();
}

void node::centerText() {
    sf::FloatRect textRect = text.getLocalBounds();
//    std::cout << textRect.left << " " << textRect.top << " " << textRect.width << " " << textRect.height << std::endl;
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    text.setPosition(pos.x, pos.y - 100);
}

void node::clearText() {
    textString = "";
    setText(textString);
}

void node::concatText(const std::string &newString) {
    if (!textString.empty()) {
        textString += "/";
    }
    textString += newString;
    setText(textString);
}

void node::setPosition(float x, float y) {
    startingPoint = {x,y};
    pos = startingPoint;
    endingPoint = startingPoint;
}

void node::rotate(sf::Vector2f& vec, float angle) {
    // Get the length of the vector
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);

    // Calculate the new angle of the vector
    float newAngle = std::atan2(vec.y, vec.x) + angle;

    // Calculate the new x and y components of the vector
    float newX = length * std::cos(newAngle);
    float newY = length * std::sin(newAngle);

    // Return the rotated vector
    vec = {newX, newY};
}



