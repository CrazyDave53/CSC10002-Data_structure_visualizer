#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_MOVABLE_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_MOVABLE_H

#include <SFML/Graphics.hpp>
#include "iostream"

class movable{
public:
    movable();
    void setEndingPoint(float x, float y);
    void updatePos();
    void changeSpeed(float m_speed);
    sf::Vector2f pos, startingPoint, endingPoint, velocity, acceleration;
    bool isMoving;
    float speed;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_MOVABLE_H
