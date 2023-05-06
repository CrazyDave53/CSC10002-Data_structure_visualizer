#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_CELL_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_CELL_H

#include "movable.h"
#include "numberSprite.h"

enum squareState{
    normalSquareState,
    highlightedSquareState,
    greenSquareState,
    redSquareState
};

class Cell : public movable, public transition{
public:
    Cell();
    Cell(int value, int index, sf::Vector2f center, bool _isNull = false);
    ~Cell();

    void setValue(int value);
    int getValue();

    void loadTexture();

    void setIndex(int index);
    int getIndex();

    void update();
    void draw(sf::RenderWindow& window);

    void setHighlighted(bool _isHighlighted);
    void setNull(bool _isNull);
//    void setState(int state);
    void setState(squareState newState, float duration);
    void setStateImmediately(squareState newState);

    bool isNull;

    numberSprite numText;
    numberSprite indexText;

    int phase;

private:
    int value;
    int index;

    bool isHighlighted;

    sf::Texture outlineSquare;
    sf::Texture highlightSquare;
    sf::Texture greenSquareTexture;
    sf::Texture redSquareTexture;

    sf::Sprite square;
    sf::Sprite fadingSquare;

    sf::Texture nullTexture;
    sf::Sprite null;

    squareState state;

    void updateFading();
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_CELL_H
