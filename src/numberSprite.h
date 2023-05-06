#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_NUMBERSPRITE_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_NUMBERSPRITE_H

#include <SFML/Graphics.hpp>
#include "transition.h"
#include "movable.h"

class numberSprite : public transition, public movable{
public:
    numberSprite(int number, sf::Vector2f center);
    void draw(sf::RenderWindow& window);
    void update(sf::Vector2f center);
    void update();
    void setOpacity(float opacity);
    void loadTexture();

    int number;
private:
    sf::Texture m_digitTextures[10];
    sf::Sprite m_digitSprites[20];
    int tens;
    int ones;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_NUMBERSPRITE_H
