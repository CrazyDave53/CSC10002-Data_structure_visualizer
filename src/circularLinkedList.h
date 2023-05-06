#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_CIRCULARLINKEDLIST_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_CIRCULARLINKEDLIST_H

#include "linkedList.h"
#include "curvedArrow.h"

class CircularLinkedList : public LinkedList{
public:
    CircularLinkedList();
    void update() override;
    void draw(sf::RenderWindow &window);

    void search(int target);
    void updateSearch();
    void updateSearchImmediately();

    void insertToHead(int value);
    void insertToTail(int value);

    void deleteHead();
    void deleteTail();


private:
    void drawArrow(sf::RenderWindow &window, sf::Vector2f startPoint, sf::Vector2f endPoint, float arrowThickness, float triangleSize);
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_CIRCULARLINKEDLIST_H
