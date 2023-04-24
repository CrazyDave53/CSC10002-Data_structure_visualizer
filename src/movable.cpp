#include "movable.h"

movable::movable() :
    pos(),
    startingPoint(),
    endingPoint(),
    velocity(),
    acceleration(),
    isMoving(),
    speed(0.001)
{
}

void movable::setEndingPoint(float x, float y) {
    startingPoint = pos;
    endingPoint.x = x;
    endingPoint.y = y;
    velocity -= velocity;
    acceleration -= acceleration;
    acceleration = (endingPoint - startingPoint);
    acceleration = acceleration * (float)(speed);
    isMoving = true;
}

void movable::updatePos() {
    if(pos == endingPoint){
        isMoving = false;
    }
    else
        isMoving = true;
    if(((endingPoint - pos).x * (endingPoint - pos).x + (endingPoint - pos).y * (endingPoint - pos).y) / ((pos - startingPoint).x * (pos - startingPoint).x + (pos - startingPoint).y * (pos - startingPoint).y) <= 0.95){
        velocity -= acceleration;
    }
    else
        velocity += acceleration;
    pos += velocity;
    if(((endingPoint - startingPoint).x * (endingPoint - startingPoint).x + (endingPoint - startingPoint).y * (endingPoint - startingPoint).y) <= ((pos - startingPoint).x * (pos - startingPoint).x + (pos - startingPoint).y * (pos - startingPoint).y)){
        acceleration -= acceleration;
        velocity -= velocity;
        startingPoint = endingPoint;
        pos = endingPoint;
    }
}

void movable::changeSpeed(float m_speed) {
    speed = m_speed;
}
