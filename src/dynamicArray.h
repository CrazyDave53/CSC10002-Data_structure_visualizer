#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_DYNAMICARRAY_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_DYNAMICARRAY_H

#include "cell.h"
#include "FileSelectionDialog.h"
#include "AlertBox.h"
#include "CodeFrame.h"
#include <string>

class DynamicArray {
public:
    DynamicArray();

    void draw(sf::RenderWindow& window);
    void update();
    void updateSizeCapacity();
    void updateText();

    void saveArrayState();
    void loadArrayState();

    void refreshArray();
    void refreshNewArray();

    void updateArrayPos(float x, float y, float _offset);
    void updateArrayPosImmediately(float x, float y, float _offset);
    void updateNewArrayPos(float x, float y, float _offset);

    void allocateNew(int sz);
    void allocateNewImmediately(int sz);

    void copyToNewArray();
    void updateCopyToNewArray();
    void updateCopyToNewArrayImmediately();

    void transferToArray();
    void updateTransferToArray();
    void updateTransferToArrayImmediately();

    void deleteArray();
    void deleteNewArray();

    void createArray(std::vector<int> v);
    void createRandom(int sz);
    void createFromFile();
    void createUserInput(std::string input);

    void search(int target);
    void updateSearch();
    void updateSearchImmediately();

    void updateElement(int index, int value);
    void updateUpdateElement();
    void updateUpdateElementImmediately();

    void insert(int index, int value);
    void updateInsert();
    void updateInsertImmediately();
    void insertToHead(int value);
    void insertToTail(int value);

    void deleteElement(int index);
    void updateDeleteElement();
    void updateDeleteElementImmediately();
    void deleteHead();
    void deleteTail();

    void allocate(int sz);



    void pause();
    void resume();
    void fastForward();
    void rewind();
    void moveToStep(int targetStep);

    bool isPausing;
private:
    std::vector<Cell> array;
    int arraySize;
    int arrayCapacity;
    sf::Text arraySizeText;
    sf::Text arrayCapacityText;
    std::string arraySizeString;
    std::string arrayCapacityString;

    std::vector<Cell> newArray;
    int newArraySize;
    int newArrayCapacity;
    sf::Text newArraySizeText;
    sf::Text newArrayCapacityText;
    std::string newArraySizeString;
    std::string newArrayCapacityString;

    float offset;

    FileDialog openDialog;

    AlertBox alertBox;

    std::vector<int> savedState;
    int savedStateSize;
    int savedStateCapacity;


    std::vector<int> stringToVector(std::string input);

    sf::Vector2f arrayPos;
    sf::Vector2f newArrayPos;

    sf::Font font;

    CodeFrame code;

    int indexNow;
    int indexCopyNow;
    int indexTransferNow;
    int step;
    int phase;
    int transferPhase;
    int searchTarget;
    int targetIndex;
    int targetValue;

    bool isCopyingToNewArray;
    bool isAllocatingNewArray;
    bool isTransferringToArray;
    bool isSearching;
    bool isUpdatingElement;
    bool isInserting;
    bool isDeleting;

    bool isMakingSpace;

};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_DYNAMICARRAY_H
