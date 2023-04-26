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
    void createList(std::vector<int> v);

    void saveListState();
    void loadListState();

    void refreshList();
    void refreshListPos();

    void search(int target);
    void updateSearch();
    void updateSearchImmediately();

    void draw(sf::RenderWindow& window);
    void update();

    void updateNodePos(float x, float y, float offset);
    void updateArrow();
    void updateText();
    void updatePrev();
    bool isArrowMoving();

    void insertToHead(int value);
    void updateInsertHead();
    void updateInsertHeadImmediately();

    void insertToTail(int value);
    void updateInsertTail();
    void updateInsertTailImmediately();

    void insertArbitrary(int value, int index);
    void updateArbitraryInsert();
    void updateArbitraryInsertImmediately();

    void deleteHead();
    void updateDeleteHead();

    void deleteTail();
    void updateDeleteTail();

    void deleteArbitrary(int index);
    void updateDeleteArbitrary();

    void rewind();
    void fastForward();

    void pause();
    void resume();
    void moveToStep(int targetStep);

    node *head;
    node *tail;
    int size;

    bool isPausing;
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

    int step;

    std::vector<int> list;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H
