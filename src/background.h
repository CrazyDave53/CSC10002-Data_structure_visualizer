#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_BACKGROUND_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_BACKGROUND_H

#include <SFML/Graphics.hpp>

class backGround{
public:
    backGround();
    void draw(sf::RenderWindow& window);
private:
    sf::Texture bgimg;
    sf::Sprite bg;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_BACKGROUND_H
