#include "staticArray.h"

StaticArray::StaticArray() :
    DynamicArray()
{

}

void StaticArray::update() {
    DynamicArray::update();
}

void StaticArray::insert(int index, int value) {
    saveArrayState();
    if(arraySize >= 9){
        alertBox.setMessage("Warning: The array is full, no more numbers can be added.");
        alertBox.setEnabled(true);
        return;
    }

    if (index < 0) {
        return;
    }
    if(index > arraySize){
        return;
    }
    if(index == arraySize && arraySize == arrayCapacity){
        return;
    }

    code.setText({
        "for (int i = arraySize; i >= targetIndex; i--)",
        "    array[i + 1] = array[i];",
        "array[targetIndex] = targetValue;"
    });

    targetIndex = index;
    targetValue = value;
    if (arrayCapacity == arraySize) {
        indexNow = arraySize - 2;
    }
    else {
        indexNow = arraySize - 1;
    }

    phase = 0;
    isInserting = true;
    step = 0;
    phase = 0;
}

void StaticArray::updateInsert() {
    if (!isInserting) {
        return;
    }
    switch (array[indexNow].phase){
        case 0:
            if (array[indexNow].isFading) {
                return;
            }

            code.deHighlightAll();
            code.setHighlight(0);

            array[indexNow].setState(highlightedSquareState, 2000);
            array[indexNow+1].setState(greenSquareState, 2000);
            array[indexNow].phase = 1;

            step++;
            break;
        case 1:
            if (array[indexNow].isFading) {
                return;
            }

            code.deHighlightAll();
            code.setHighlight(1);

            array[indexNow+1].setValue(array[indexNow].getValue());
            array[indexNow+1].setNull(false);
            array[indexNow+1].numText.pos = array[indexNow].pos;
            array[indexNow+1].numText.setEndingPoint(array[indexNow+1].pos.x, array[indexNow+1].pos.y);
            array[indexNow].phase = 2;

            step++;
            break;
        case 2:
            if (array[indexNow+1].numText.isMoving) {
                return;
            }

            if (indexNow == targetIndex) {
                array[indexNow].setState(greenSquareState, 2000);
                array[indexNow+1].setState(normalSquareState, 2000);
                array[indexNow].phase = 3;
            } else {
                array[indexNow].setState(normalSquareState, 2000);
                array[indexNow+1].setState(normalSquareState, 2000);
                array[indexNow].phase = 0;
                indexNow--;
            }
            step++;
            break;
        case 3:
            if (array[indexNow].isFading) {
                return;
            }

            code.deHighlightAll();
            code.setHighlight(2);

            array[indexNow].setValue(targetValue);
            array[indexNow].setNull(false);
            array[indexNow].setState(normalSquareState, 2000);
            array[indexNow].phase = 0;

            isInserting = false;
            phase = 0;

            step++;
            break;
    }
}

void StaticArray::updateInsertImmediately() {
    if (!isInserting) {
        return;
    }
    switch (array[indexNow].phase){
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);

            array[indexNow].setStateImmediately(highlightedSquareState);
            array[indexNow+1].setStateImmediately(greenSquareState);
            array[indexNow].phase = 1;

            step++;
            break;
        case 1:
            code.deHighlightAll();
            code.setHighlight(1);

            array[indexNow+1].setValue(array[indexNow].getValue());
            array[indexNow+1].setNull(false);
            array[indexNow].phase = 2;

            step++;
            break;
        case 2:
            if (indexNow == targetIndex) {
                array[indexNow].setStateImmediately(greenSquareState);
                array[indexNow+1].setStateImmediately(normalSquareState);
                array[indexNow].phase = 3;
            } else {
                array[indexNow].setStateImmediately(normalSquareState);
                array[indexNow+1].setStateImmediately(normalSquareState);
                array[indexNow].phase = 0;
                indexNow--;
            }
            step++;
            break;
        case 3:
            code.deHighlightAll();
            code.setHighlight(2);

            array[indexNow].setValue(targetValue);
            array[indexNow].setNull(false);
            array[indexNow].setStateImmediately(normalSquareState);
            array[indexNow].phase = 0;

            isInserting = false;
            phase = 0;

            step++;
            break;
    }
}


