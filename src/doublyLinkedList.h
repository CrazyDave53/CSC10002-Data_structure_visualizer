#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_DOUBLYLINKEDLIST_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_DOUBLYLINKEDLIST_H

#include "LinkedList.h"

class DoublyLinkedList : public LinkedList{
public:
    void createRandom(int sz);
    void createList(std::vector<int> v);

    void loadListState();
    void update();

    void updateInsertHead();

    void insertToHead(int value);

    void updateInsertHeadImmediately();

    void insertToTail(int value);

    void updateInsertTail();

    void updateInsertTailImmediately();

    void insertArbitrary(int value, int index);

    void updateArbitraryInsert();

    void updateArbitraryInsertImmediately();

    void deleteHead();

    void deleteTail();

    void deleteArbitrary(int index);

    void updateDeleteArbitrary();

    void updateDeleteArbitraryImmediately();
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_DOUBLYLINKEDLIST_H
