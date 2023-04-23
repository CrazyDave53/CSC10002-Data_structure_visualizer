#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H

#include "node.h"
#include "codeFrame.h"
class LinkedList{
public:
    LinkedList();
    ~LinkedList();
    void deleteList();
    void createRandom(int sz);

    void refreshList();

    void search(int target);
    void updateSearch();
    void updateSearchImmediately();

    void draw(sf::RenderWindow& window);
    void update();

    void updateNodePos(float x, float y, float offset);
    void updateArrow();
    void updateText();

    void insertToHead(int value);
    void updateInsertHead();
    void insertToTail(int value);
    void updateInsertTail();
    void insertArbitrary(int value, int index);
    void updateArbitraryInsert();

    void deleteHead();
    void updateDeleteHead();

    void deleteTail();
    void updateDeleteTail();

    void deleteArbitrary(int index);
    void updateDeleteArbitrary();

    node *head;
    node *tail;
    int size;
private:
    node* cur;
    CodeFrame code;
    int searchTarget;
    bool isSearching;

    int insertValue;
    int insertIndex;
    node* preInsert;
    node* afterInsert;
    node* insertNode;
    int indexNow;
    bool isInserting;
    bool isInsertingHead;
    bool isInsertingTail;
    int phase;

    node* deletedNode;
    bool isDeletingHead;

    bool isDeletingTail;
    node* preDelete;

    bool isDeletingArbitrary;
    int deleteIndex;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H
