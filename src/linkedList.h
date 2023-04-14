#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H

#include "node.h"

class LinkedList{
public:
    LinkedList();
    ~LinkedList();
    void deleteList();
    void createRandom(int size);
    void search(int n);

    void draw(sf::RenderWindow& window);
    void update();
private:
    void search(node * node, int n);
    node *head, * pt;
    time 
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H
