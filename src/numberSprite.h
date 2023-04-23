#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_NUMBERSPRITE_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_NUMBERSPRITE_H

#include <SFML/Graphics.hpp>
#include "transition.h"

class numberSprite : public transition{
public:
    numberSprite(int number, sf::Vector2f center);
    void draw(sf::RenderWindow& window);
    void update(sf::Vector2f center);
    void setOpacity(float opacity);
private:
    sf::Texture m_digitTextures[10];
    sf::Sprite m_digitSprites[20];
    int tens;
    int ones;
    int number;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_NUMBERSPRITE_H
