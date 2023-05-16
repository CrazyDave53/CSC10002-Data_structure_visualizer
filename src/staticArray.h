#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_STATICARRAY_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_STATICARRAY_H

#include "dynamicArray.h"

class StaticArray : public DynamicArray{
public:
    StaticArray();

    void update() override;

    void insert(int value, int index) override;
    void updateInsert() override;
    void updateInsertImmediately() override;

    void insertToTail(int value) override;

};

#endif
