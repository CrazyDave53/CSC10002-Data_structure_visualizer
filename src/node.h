#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_NODE_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_NODE_H

#include "movable.h"
#include "arrow.h"
#include "numberSprite.h"
#include "../Gui/Theme.hpp"


class node: public movable{
public:
    node(int number, float x, float y);
    void draw(sf::RenderWindow& window);
    void setHighlight(bool isHiglighted);
    void update();
    node *next;
    Arrow arrow;
    int number;
private:
    sf::Texture osuCircle;
    sf::Texture highlightCircle;
    sf::Sprite circle;
    sf::Vector2f inPivot;
    sf::Vector2f outPivot;
    numberSprite numText;
    sf::Font font;
    bool highlighted;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_NODE_H
