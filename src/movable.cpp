#include "movable.h"

movable::movable() :
    pos(),
    startingPoint(),
    endingPoint(),
    velocity(),
    acceleration()
{
}

void movable::setEndingPoint(float x, float y) {
    startingPoint = pos;
    endingPoint.x = x;
    endingPoint.y = y;
    velocity -= velocity;
    acceleration -= acceleration;
    acceleration = (endingPoint - startingPoint);
    acceleration = acceleration * (float)(0.001);
}

void movable::updatePos() {
    if(pos == endingPoint){
        isMoving = false;
    }
    isMoving = true;
    if((endingPoint - pos).x / (pos - startingPoint).x <= 0.95){
        velocity -= acceleration;
    }
    else
        velocity += acceleration;
    pos += velocity;
    if((endingPoint - pos).x / (pos - startingPoint).x <= 0){
        acceleration -= acceleration;
        velocity -= velocity;
        startingPoint = endingPoint;
        pos = endingPoint;
    }
}
