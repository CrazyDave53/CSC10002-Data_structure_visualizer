#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_ARROW_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_ARROW_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "movable.h"


class Arrow : public movable{
public:
    Arrow(sf::Vector2f start, sf::Vector2f end);
    void setThickness(float thickness);
    void setTriangleSize(float size);
    void setStart(sf::Vector2f start);
    void setEnd(sf::Vector2f end);
    void moveEnd(sf::Vector2f end);
    void draw(sf::RenderWindow& window);
    void update();
    void setOpacity(float opacity);
private:
    sf::RectangleShape m_rect;
    sf::ConvexShape m_triangle;
    float m_thickness;
    float m_triangleSize;
    sf::Vector2f m_start;
    sf::Vector2f m_end;
};


#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_ARROW_H
