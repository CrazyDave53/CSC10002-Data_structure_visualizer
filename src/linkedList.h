#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H

#include "node.h"
#include "codeFrame.h"
#include "FileSelectionDialog.h"
#include "AlertBox.h"

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void onEvent(sf::Event event);

    void deleteList();

    virtual void createRandom(int sz);
    void createUserInput(std::string input);
    void createFromFile();

    virtual void createList(std::vector<int> v);

    int getSize();

    void saveListState();

    virtual void loadListState();

    void refreshList();
    void refreshListPos();

    virtual void search(int target);

    virtual void updateSearch();

    virtual void updateSearchImmediately();

    void updateNode(int index, int value);
    void updateUpdateNode();
    void updateUpdateNodeImmediately();

    virtual void draw(sf::RenderWindow& window);

    virtual void update();

    void updateNodePos(float x, float y, float offset);
    void updateArrow();
    void updateText();
    void updatePrev();
    bool isArrowMoving();

    virtual void insertToHead(int value);

    virtual void updateInsertHead();

    virtual void updateInsertHeadImmediately();

    virtual void insertToTail(int value);

    virtual void updateInsertTail();

    virtual void updateInsertTailImmediately();

    virtual void insertArbitrary(int value, int index);

    virtual void updateArbitraryInsert();

    virtual void updateArbitraryInsertImmediately();

    virtual void deleteHead();
    void updateDeleteHead();
    void updateDeleteHeadImmediately();

    virtual void deleteTail();
    void updateDeleteTail();
    void updateDeleteTailImmediately();

    virtual void deleteArbitrary(int index);

    virtual void updateDeleteArbitrary();

    virtual void updateDeleteArbitraryImmediately();

    void rewind();
    void fastForward();

    void pause();
    void resume();
    void moveToStep(int targetStep);

    node *head;
    node *tail;
    int size;

    bool isPausing;

    AlertBox alertBox;
private:
    std::vector<int> stringToVector(std::string input);
    FileDialog openDialog;

protected:
    node* afterInsert;
    std::vector<int> list;
    node* insertNode;
    bool isInserting;
    int phase;
    bool isInsertingHead;
    CodeFrame code;
    int insertIndex;
    node* preInsert;
    int step;

    node* cur;
    int searchTarget;
    bool isSearching;

    int updateIndex;
    int updateValue;
    bool isUpdating;

    int insertValue;
    int indexNow;
    bool isInsertingTail;

    node* deletedNode;
    bool isDeletingHead;

    bool isDeletingTail;
    node* preDelete;
    node* afterDelete;

    bool isDeletingArbitrary;
    int deleteIndex;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_LINKEDLIST_H
