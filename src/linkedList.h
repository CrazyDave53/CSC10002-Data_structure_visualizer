#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H

#include "node.h"

class LinkedList{
public:
    LinkedList();
    ~LinkedList();
    void deleteList();
    void createRandom(int sz);

    void search(int target);
    void updateSearch();

    void draw(sf::RenderWindow& window);
    void update();

    void updateNodePos(float x, float y, float offset);
    void updateArrow();

    void insertToHead(int value);
    void insertToTail(int value);
    void insertArbitrary(int value, int index);
    void updateArbitraryInsert();

    node *head;
    node *tail;
    int size;
private:
    node* cur;
    int searchTarget;
    bool isSearching;

    int insertValue;
    int insertIndex;
    node* preInsert;
    node* afterInsert;
    node* insertNode;
    int indexNow;
    bool isInserting;
    int phase;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H
