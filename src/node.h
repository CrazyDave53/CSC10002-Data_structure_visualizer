#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_NODE_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_NODE_H

#include "movable.h"
#include "transition.h"
#include "arrow.h"
#include "numberSprite.h"
#include "../Gui/Theme.hpp"

enum circleState{
    normal,
    highlighted,
    green,
    red,
    invisible
};

class node: public movable, public transition{
public:
    node(int number, float x, float y);
    void draw(sf::RenderWindow& window);
    void setState(circleState newState, float duration);
    void setStateImmediately(circleState newState);
    void setPosition(float x, float y);
    void update();
    void updateArrow();
    void updateFading();
    void appear();
    void setText(const std::string& newString);
    void centerText();
    void clearText();
    void concatText(const std::string& newString);
    node *next;
    node *prev;
    Arrow arrow;
    int number;
    int phase;
    sf::Vector2f inPivot;
    sf::Vector2f outPivot;
private:
    sf::Texture osuCircle;
    sf::Texture highlightCircle;
    sf::Texture greenCircle;
    sf::Texture redCircle;
    sf::Texture invisibleCircle;
    sf::Sprite circle;
    sf::Sprite fadingCircle;
    numberSprite numText;
    sf::Text text;
    sf::Font font;
    std::string textString;
    circleState state;//0: normal, 1:blue, 2:red, 3:green
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_NODE_H
