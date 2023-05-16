#include "dynamicArray.h"


DynamicArray::DynamicArray() :
    array(),
    arraySize(),
    arrayCapacity(),
    newArray(),
    newArraySize(),
    newArrayCapacity(),
    offset(170),
    openDialog(),
    alertBox(),
    indexNow(0),
    step(),
    phase(),
    savedState(),
    arrayPos(400, 200),
    newArrayPos(400, 500),
    font(),
    arraySizeText(),
    arrayCapacityText(),
    newArraySizeText(),
    newArrayCapacityText(),
    arraySizeString(),
    arrayCapacityString(),
    newArraySizeString(),
    newArrayCapacityString(),
    isCopyingToNewArray(false),
    isPausing(false),
    isAllocatingNewArray(false),
    isTransferringToArray(false),
    isSearching(false),
    isUpdatingElement(false),
    isInserting(false),
    isDeleting(false),
    isMakingSpace(false),
    code()
{
    font.loadFromFile("./fonts/ARLRDBD.TTF");

    arraySizeText.setFont(font);
    arraySizeText.setCharacterSize(40);
    arraySizeText.setFillColor(sf::Color::White);
    arraySizeText.setStyle(sf::Text::Bold);
    arraySizeString = std::string("Size: " + std::to_string(arraySize));
    arraySizeText.setString(arraySizeString);
    arraySizeText.setPosition(arrayPos.x - 350, arrayPos.y - 50);

    arrayCapacityText.setFont(font);
    arrayCapacityText.setCharacterSize(40);
    arrayCapacityText.setFillColor(sf::Color::White);
    arrayCapacityText.setStyle(sf::Text::Bold);
    arrayCapacityString = std::string("Capacity: " + std::to_string(arrayCapacity));
    arrayCapacityText.setString(arrayCapacityString);
    arrayCapacityText.setPosition(arrayPos.x - 350, arrayPos.y);

    newArraySizeText.setFont(font);
    newArraySizeText.setCharacterSize(40);
    newArraySizeText.setFillColor(sf::Color::White);
    newArraySizeText.setStyle(sf::Text::Bold);
    newArraySizeString = std::string("Size: " + std::to_string(newArraySize));
    newArraySizeText.setString(newArraySizeString);
    newArraySizeText.setPosition(newArrayPos.x - 350, newArrayPos.y - 50);

    newArrayCapacityText.setFont(font);
    newArrayCapacityText.setCharacterSize(40);
    newArrayCapacityText.setFillColor(sf::Color::White);
    newArrayCapacityText.setStyle(sf::Text::Bold);
    newArrayCapacityString = std::string("Capacity: " + std::to_string(newArrayCapacity));
    newArrayCapacityText.setString(newArrayCapacityString);
    newArrayCapacityText.setPosition(newArrayPos.x - 350, newArrayPos.y);

    array.reserve(9);
    deleteArray();
    newArray.reserve(9);
    deleteNewArray();
}

void DynamicArray::onEvent(sf::Event event) {
    alertBox.isCloseButtonPressed(event);
}

void DynamicArray::update() {
    updateText();

    for (auto & i : array) {
        i.update();
    }
    for (auto & i : newArray) {
        i.update();
    }
    if(!isPausing) {
        if(isSearching){
            updateSearch();
        }
        if(isUpdatingElement){
            updateUpdateElement();
        }
        if(isInserting){
            updateInsert();
        }
        if(isDeleting){
            updateDeleteElement();
        }
    }

}

void DynamicArray::updateSizeCapacity() {
    arraySize = 0;
    for (auto & i : array) {
        arraySize += !i.isNull;
    }
    arrayCapacity = array.size();

    newArraySize = 0;
    for (auto & i : newArray) {
        newArraySize += !i.isNull;
    }
    newArrayCapacity = newArray.size();
}

void DynamicArray::updateText() {
    updateSizeCapacity();

    arraySizeString = std::string("Size: " + std::to_string(arraySize));
    arrayCapacityString = std::string("Capacity: " + std::to_string(arrayCapacity));

    arraySizeText.setString(arraySizeString);
    arrayCapacityText.setString(arrayCapacityString);

    newArraySizeString = std::string("Size: " + std::to_string(newArraySize));
    newArrayCapacityString = std::string("Capacity: " + std::to_string(newArrayCapacity));

    newArraySizeText.setString(newArraySizeString);
    newArrayCapacityText.setString(newArrayCapacityString);

    if(arraySize > 0) {
        arraySizeText.setPosition(array[0].pos.x - 350, array[0].pos.y - 50);
        arrayCapacityText.setPosition(array[0].pos.x - 350, array[0].pos.y);
    }

    if(newArraySize > 0) {
        newArraySizeText.setPosition(newArray[0].pos.x - 350, newArray[0].pos.y - 50);
        newArrayCapacityText.setPosition(newArray[0].pos.x - 350, newArray[0].pos.y);
    }

}

void DynamicArray::draw(sf::RenderWindow& window) {
    update();
    for (auto & i : array) {
        i.draw(window);
    }
    for (auto & i : newArray) {
        i.draw(window);
    }
    if(arrayCapacity > 0) {
        window.draw(arraySizeText);
        window.draw(arrayCapacityText);
    }
    if(newArrayCapacity > 0) {
        window.draw(newArraySizeText);
        window.draw(newArrayCapacityText);
    }

    sf::Vector2f pos = sf::Vector2f(1920 - 100, 1080 - 100) - code.getSize();
    code.setPosition(pos.x, pos.y);
    code.draw(window);

    alertBox.draw(window);
}

void DynamicArray::saveArrayState() {
    savedState.clear();
    for(auto & i : array){
        savedState.push_back(i.getValue());
    }
}

void DynamicArray::loadArrayState() {
    deleteArray();
    if(savedState.empty())
        return;
    if(savedState.size() > 9){
        savedState.resize(9);
        alertBox.setMessage("Warning: Maximum capacity of 9 reached, only allocate for 9 elements.");
        alertBox.setEnabled(true);
    }
    for (int i = 0; i < savedState.size(); i++) {
        array.emplace_back(savedState[i], i, arrayPos + sf::Vector2f(i * offset, 0), false);
        array[i].loadTexture();
        array[i].pos = arrayPos + sf::Vector2f(i * offset, 0);
        array[i].setEndingPoint(arrayPos.x + i * offset, arrayPos.y);
    }
    updateSizeCapacity();
    refreshArray();
}

void DynamicArray::refreshArray() {
    for (auto & i : array) {
        i.loadTexture();
        i.phase = 0;
        i.setStateImmediately(normalSquareState);
    }
}

void DynamicArray::updateArrayPos(float x, float y, float _offset) {
    for (int i = 0; i < array.size(); i++) {
        array[i].setEndingPoint(i * _offset + x, y);
    }
}

void DynamicArray::updateArrayPosImmediately(float x, float y, float _offset) {
    for (int i = 0; i < array.size(); i++) {
        array[i].pos = {i * _offset + x, y};
        array[i].setEndingPoint(i * _offset + x, y);
        array[i].updatePos();
    }

}

void DynamicArray::updateNewArrayPos(float x, float y, float _offset) {
    for (int i = 0; i < newArray.size(); i++) {
        newArray[i].setEndingPoint(i * _offset + x, y);
    }
}

void DynamicArray::allocateNew(int sz) {
    deleteNewArray();
    newArrayCapacity = sz;
    newArraySize = 0;

    code.setText({
        "newArray = new int[" + std::to_string(sz) +"];"
    });
    code.deHighlightAll();
    code.setHighlight(0);

    if(sz > 9){
        newArrayCapacity = 9;
        alertBox.setMessage("Warning: Maximum capacity of 9 reached, only allocate for 9 elements.");
        alertBox.setEnabled(true);
    }
    for (int i = 0; i < sz; i++) {
        newArray.emplace_back(0, i, newArrayPos + sf::Vector2f(i * offset, 0), true);
        newArray[i].setEndingPoint(i * offset + newArrayPos.x, newArrayPos.y);
    }

    step++;
}

void DynamicArray::allocateNewImmediately(int sz) {
    deleteNewArray();
    newArrayCapacity = sz;
    newArraySize = 0;

    code.setText({
                         "newArray = new int[" + std::to_string(sz) +"];"
                 });
    code.deHighlightAll();
    code.setHighlight(0);

    if(sz > 9){
        newArrayCapacity = 9;
        alertBox.setMessage("Warning: Maximum capacity of 9 reached, only allocate for 9 elements.");
        alertBox.setEnabled(true);
    }
    for (int i = 0; i < sz; i++) {
        newArray.emplace_back(0, i, newArrayPos + sf::Vector2f(i * offset, 0), true);
        newArray[i].pos = newArrayPos + sf::Vector2f(i * offset, 0);
        newArray[i].setEndingPoint(i * offset + newArrayPos.x, newArrayPos.y);
    }

    step++;
}

void DynamicArray::copyToNewArray() {
    if(arraySize == 0 || newArrayCapacity == 0){
        return;
    }
    code.setText({
        "for (int i = 0; i < arraySize; i++)",
        "    newArray[i] = array[i];"
    });
    indexCopyNow = 0;
    isCopyingToNewArray = true;
}

void DynamicArray::updateCopyToNewArray() {
    if (!isCopyingToNewArray || isPausing) {
        return;
    }
    switch(newArray[indexCopyNow].phase){
        case 0:
            newArray[indexCopyNow].phase = 1;
            newArray[indexCopyNow].setState(highlightedSquareState, 2000);

            code.deHighlightAll();
            code.setHighlight(0);

            step++;
            break;
        case 1:
            if (newArray[indexCopyNow].isFading) {
                return;
            }
            newArray[indexCopyNow].phase = 2;
            newArray[indexCopyNow].setValue(array[indexCopyNow].getValue());
            newArray[indexCopyNow].setNull(false);
            newArray[indexCopyNow].numText.pos = array[indexCopyNow].pos;
            newArray[indexCopyNow].numText.setEndingPoint(newArray[indexCopyNow].pos.x, newArray[indexCopyNow].pos.y);
            newArray[indexCopyNow].numText.update();

            code.deHighlightAll();
            code.setHighlight(1);

            step++;
            break;
        case 2:
            if (newArray[indexCopyNow].numText.isMoving) {
                return;
            }
            newArray[indexCopyNow].phase = 0;
            newArray[indexCopyNow].setState(normalSquareState, 2000);

            indexCopyNow++;
            if (indexCopyNow == std::min(arraySize, newArrayCapacity)) {
                indexCopyNow = 0;
                step++;
                isCopyingToNewArray = false;
                return;
            }
            step++;
            break;
    }
}

void DynamicArray::updateCopyToNewArrayImmediately() {
    if (!isCopyingToNewArray) {
        return;
    }
    switch(newArray[indexCopyNow].phase){
        case 0:
            newArray[indexCopyNow].phase = 1;
            newArray[indexCopyNow].setStateImmediately(highlightedSquareState);

            code.deHighlightAll();
            code.setHighlight(0);

            step++;
            break;
        case 1:
            newArray[indexCopyNow].phase = 2;
            newArray[indexCopyNow].setValue(array[indexCopyNow].getValue());
            newArray[indexCopyNow].setNull(false);
//            newArray[indexNow].numText.update();

            code.deHighlightAll();
            code.setHighlight(1);

            step++;
            break;
        case 2:
            newArray[indexCopyNow].phase = 0;
            newArray[indexCopyNow].setStateImmediately(normalSquareState);

            indexCopyNow++;
            if (indexCopyNow == std::min(arraySize, newArrayCapacity)) {
                indexCopyNow = 0;
                step++;
                isCopyingToNewArray = false;
                return;
            }
            step++;
            break;
    }
}

void DynamicArray::transferToArray() {
    if(newArrayCapacity == 0){
        return;
    }
    code.setText({
        "delete [] array;",
        "array = newArray;"
    });
    indexTransferNow = 0;
    transferPhase = 0;
    isTransferringToArray = true;
}

void DynamicArray::updateTransferToArray() {
    if (!isTransferringToArray || isPausing) {
        return;
    }
    switch(transferPhase){
        case 0:
            updateArrayPos(-200, -200, offset);
            code.deHighlightAll();
            code.setHighlight(0);

            transferPhase = 1;
            step++;
            break;
        case 1:
            if (array.size() > 0 && array[0].isMoving) {
                return;
            }
            array.clear();
            array = newArray;
            refreshArray();
            newArray.clear();
            updateArrayPos(arrayPos.x, arrayPos.y, offset);

            code.deHighlightAll();
            code.setHighlight(1);

            transferPhase = 2;
            step++;
            break;
        case 2:
            if (array[0].isMoving) {
                return;
            }
            transferPhase = 0;
            isTransferringToArray = false;
            step++;
            break;
    }
}

void DynamicArray::updateTransferToArrayImmediately() {
    if (!isTransferringToArray) {
        return;
    }
    switch(transferPhase){
        case 0:
            updateArrayPosImmediately(-200, -200, offset);
            code.deHighlightAll();
            code.setHighlight(0);

            transferPhase = 1;
            step++;
            break;
        case 1:
            array.clear();
            array = newArray;
            refreshArray();
            newArray.clear();
            updateArrayPosImmediately(arrayPos.x, arrayPos.y, offset);

            code.deHighlightAll();
            code.setHighlight(1);

            transferPhase = 2;
            step++;
            break;
        case 2:
            transferPhase = 0;
            isTransferringToArray = false;
            step++;
            break;
    }
}

void DynamicArray::deleteArray() {
    array.clear();
}

void DynamicArray::deleteNewArray() {
    newArray.clear();
}

void DynamicArray::createArray(std::vector<int> v) {
    deleteArray();
    arraySize = v.size();
    if(v.empty())
        return;
    if(v.size() > 9){
        v.resize(9);
        alertBox.setMessage("Warning: The input is too long, only the first 9 numbers will be used.");
        alertBox.setEnabled(true);
    }
    for (int i = 0; i < v.size(); i++) {
        array.emplace_back(v[i], i, sf::Vector2f(-100, -100), false);
        array[i].setEndingPoint(arrayPos.x + i * offset, arrayPos.y);
    }
}

void DynamicArray::createRandom(int sz) {
    deleteArray();
    std::vector<int> v;
    for (int i = 0; i < sz; i++) {
        v.push_back(rand() % 100);
    }
    createArray(v);
}

std::vector<int> DynamicArray::stringToVector(std::string input) {
    std::vector<int> v;
    std::string temp;
    for (char i : input) {
        if(i == ','){
            try{
                v.push_back(std::stoi(temp));
            }
            catch (std::invalid_argument& e){
                alertBox.setMessage("Error: Invalid input. Please enter a list of integers separated by commas.");
                alertBox.setEnabled(true);
                return {};
            }
            temp.clear();
        }
        else
            temp += i;
    }
    if(!temp.empty())
        v.push_back(std::stoi(temp));
    return v;
}

void DynamicArray::createFromFile() {
    std::string content = openDialog.ShowOpenFileDialog();
    createArray(stringToVector(content));
}

void DynamicArray::createUserInput(std::string input) {
    deleteArray();
    createArray(stringToVector(input));
}

void DynamicArray::search(int target) {
    saveArrayState();
    if(array.empty())
        return;

    code.setText({
        "for(int i = 0; i < arraySize; i++)",
        "    if(array[i] == target)",
        "        return i;",
        "return NOT_FOUND;"
    });
    code.deHighlightAll();
    indexNow = 0;
    step = 0;
    searchTarget = target;
    isSearching = true;
    isPausing = false;
}

void DynamicArray::updateSearch() {
    if (!isSearching) {
        return;
    }
    switch (array[indexNow].phase) {
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);

            array[indexNow].setState(highlightedSquareState, 2000);
            array[indexNow].phase = 1;

            step++;
            break;
        case 1:
            if (array[indexNow].isFading) {
                return;
            }

            code.deHighlightAll();
            code.setHighlight(1);

            if (array[indexNow].getValue() == searchTarget) {
                array[indexNow].setState(greenSquareState, 2000);
                array[indexNow].phase = 3;
            } else {
                array[indexNow].setState(redSquareState, 2000);
                array[indexNow].phase = 2;
            }

            step++;
            break;
        case 2:
            if (array[indexNow].isFading) {
                return;
            }
            array[indexNow].phase = 0;
            array[indexNow].setState(normalSquareState, 2000);
            indexNow++;
            if (indexNow == arraySize) {
                code.deHighlightAll();
                code.setHighlight(3);

                indexNow = 0;
                isSearching = false;
                step++;
                return;
            }
            step++;
            break;
        case 3:
            if (array[indexNow].isFading) {
                return;
            }
            code.deHighlightAll();
            code.setHighlight(2);

            array[indexNow].phase = 0;
            array[indexNow].setState(normalSquareState, 10000);

            indexNow = 0;
            isSearching = false;
            step++;
            break;
    }
}

void DynamicArray::updateSearchImmediately() {
    if (!isSearching) {
        return;
    }
    switch (array[indexNow].phase) {
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);

            array[indexNow].setStateImmediately(highlightedSquareState);
            array[indexNow].phase = 1;

            step++;
            break;
        case 1:
            code.deHighlightAll();
            code.setHighlight(1);

            if (array[indexNow].getValue() == searchTarget) {
                array[indexNow].setStateImmediately(greenSquareState);
                array[indexNow].phase = 3;
            } else {
                array[indexNow].setStateImmediately(redSquareState);
                array[indexNow].phase = 2;
            }

            step++;
            break;
        case 2:
            array[indexNow].phase = 0;
            array[indexNow].setStateImmediately(normalSquareState);
            indexNow++;
            if (indexNow == arraySize) {
                code.deHighlightAll();
                code.setHighlight(3);

                indexNow = 0;
                isSearching = false;
                step++;
                return;
            }
            step++;
            break;
        case 3:
            code.deHighlightAll();
            code.setHighlight(2);

            array[indexNow].phase = 0;
            array[indexNow].setStateImmediately(normalSquareState);

            indexNow = 0;
            isSearching = false;
            step++;
            break;
    }
}

void DynamicArray::updateElement(int index, int value) {
    saveArrayState();
    if (index < 0 || index >= arraySize) {
        return;
    }
    code.setText({
        "array[" + std::to_string(index) + "] = " + std::to_string(value) + ";"
    });
    code.deHighlightAll();
    code.setHighlight(0);

    targetIndex = index;
    targetValue = value;

    isUpdatingElement = true;
    isPausing = false;
    step = 0;
}

void DynamicArray::updateUpdateElement() {
    if (!isUpdatingElement) {
        return;
    }
    switch (array[targetIndex].phase){
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);

            array[targetIndex].setState(highlightedSquareState, 2000);
            array[targetIndex].phase = 1;

            step++;
            break;
        case 1:
            if (array[targetIndex].isFading) {
                return;
            }

            array[targetIndex].setValue(targetValue);
            array[targetIndex].setState(greenSquareState, 2000);
            array[targetIndex].phase = 2;

            step++;
            break;
        case 2:
            if (array[targetIndex].isFading) {
                return;
            }

            array[targetIndex].phase = 0;
            array[targetIndex].setState(normalSquareState, 2000);

            isUpdatingElement = false;
            step++;
            break;
    }
}

void DynamicArray::updateUpdateElementImmediately() {
    if (!isUpdatingElement) {
        return;
    }
    switch (array[targetIndex].phase){
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);

            array[targetIndex].setStateImmediately(highlightedSquareState);
            array[targetIndex].phase = 1;

            step++;
            break;
        case 1:
            array[targetIndex].setValue(targetValue);
            array[targetIndex].setStateImmediately(greenSquareState);
            array[targetIndex].phase = 2;

            step++;
            break;
        case 2:
            array[targetIndex].phase = 0;
            array[targetIndex].setStateImmediately(normalSquareState);

            isUpdatingElement = false;
            step++;
            break;
    }
}

void DynamicArray::insert(int index, int value) {
    saveArrayState();
    if(arraySize >= 9){
        alertBox.setMessage("Warning: The array is full, no more numbers can be added.");
        alertBox.setEnabled(true);
        return;
    }

    if (index < 0 || index > arraySize) {
        return;
    }

    targetIndex = index;
    targetValue = value;
    indexNow = arraySize - 1;

    phase = 0;
    isInserting = true;
    if(arraySize == arrayCapacity)
        isMakingSpace = true;
    else
        isMakingSpace = false;

    isAllocatingNewArray = false;
    isCopyingToNewArray = false;
    isTransferringToArray = false;
    indexCopyNow = 0;
    indexTransferNow = 0;


    step = 0;
    phase = 0;
}

void DynamicArray::updateInsert() {
    if (!isInserting) {
        return;
    }
    if (isCopyingToNewArray) {
        updateCopyToNewArray();
        return;
    }
    if (isTransferringToArray) {
        updateTransferToArray();
        return;
    }
    if(isMakingSpace){
        switch (phase){
            case 0:
                allocateNew(arraySize + 1);
                phase = 1;
                step++;
                return;
            case 1:
                if(newArray[0].isMoving){
                    return;
                }
                copyToNewArray();
                phase = 2;
                step++;
                return;
            case 2:
                if(isCopyingToNewArray){
                    return;
                }
                transferToArray();
                phase = 3;
                step++;
                return;
            case 3:
                if(isTransferringToArray){
                    return;
                }

                code.setText({
                     "for (int i = arraySize-1; i > targetIndex; i--)",
                     "    array[i] = array[i - 1];",
                     "array[targetIndex] = targetValue;"
                });

                phase = 4;
                step++;
                return;
        }
    } else
        phase = 4;

    if (targetIndex == arraySize) {
        switch (array[targetIndex].phase){
            case 0:
                code.setText({
                                     "array[arraySize] = targetValue;"
                             });
                code.deHighlightAll();
                code.setHighlight(0);

                array[arraySize].setState(greenSquareState,2000);
                array[arraySize].phase = 1;

                step++;
                return;

            case 1:
                if (array[arraySize].isFading) {
                    return;
                }
                code.deHighlightAll();
                code.setHighlight(0);

                array[arraySize].setValue(targetValue);
                array[arraySize].setNull(false);

                array[arraySize].setState(normalSquareState,2000);

                array[arraySize].phase = 0;
                isInserting = false;
                step++;
                return;

        }
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

void DynamicArray::updateInsertImmediately() {
    if (!isInserting) {
        return;
    }
    if (isCopyingToNewArray) {
        updateCopyToNewArrayImmediately();
        return;
    }
    if (isTransferringToArray) {
        updateTransferToArrayImmediately();
        return;
    }
    if(isMakingSpace){
        switch (phase){
            case 0:
                allocateNewImmediately(arraySize + 1);
                phase = 1;
                return;
            case 1:
                copyToNewArray();
                updateCopyToNewArrayImmediately();
                phase = 2;
                return;
            case 2:
                transferToArray();
                updateTransferToArrayImmediately();
                phase = 3;
                return;
            case 3:
                code.setText({
                    "for (int i = arraySize; i >= targetIndex; i--)",
                    "    array[i + 1] = array[i];",
                    "array[targetIndex] = targetValue;"
                });
                phase = 4;
                step++;
                return;
        }
    } else
        phase = 4;
    if (targetIndex == arraySize) {
        switch (array[targetIndex].phase){
            case 0:
                code.setText({
                                     "array[arraySize] = targetValue;"
                             });
                code.deHighlightAll();
                code.setHighlight(0);

                array[arraySize].setStateImmediately(greenSquareState);

                array[arraySize].phase = 1;
                step++;
                return;

            case 1:
                code.deHighlightAll();
                code.setHighlight(0);

                array[arraySize].setValue(targetValue);
                array[arraySize].setNull(false);

                array[arraySize].setStateImmediately(normalSquareState);

                array[arraySize].phase = 0;
                isInserting = false;
                step++;
                return;

        }
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

            step++;
            break;
    }
}

void DynamicArray::insertToHead(int value) {
    insert(0, value);
}

void DynamicArray::insertToTail(int value) {
    insert(arraySize, value);
}

void DynamicArray::deleteElement(int index) {
    saveArrayState();
    if (index < 0 || index >= arraySize) {
        return;
    }

    targetIndex = index;
    indexNow = index;

    code.setText({
        "for (int i = targetIndex; i < arraySize - 1; i++)",
        "    array[i] = array[i + 1];",
        "arraySize--;"
    });

    phase = 0;
    isDeleting = true;

    step = 0;
    phase = 0;
}

void DynamicArray::updateDeleteElement() {
    if (!isDeleting) {
        return;
    }
    if (indexNow < arraySize - 1) {
        switch (array[indexNow].phase){
            case 0:
                if(array[indexNow].isFading) {
                    return;
                }
                code.deHighlightAll();
                code.setHighlight(0);

                array[indexNow].setState(highlightedSquareState, 2000);
                array[indexNow+1].setState(greenSquareState, 2000);
                array[indexNow].phase = 1;

                step++;
                return;
            case 1:
                if (array[indexNow].isFading) {
                    return;
                }
                code.deHighlightAll();
                code.setHighlight(1);

                array[indexNow].setValue(array[indexNow+1].getValue());
                array[indexNow].setNull(false);
                array[indexNow].numText.pos = array[indexNow+1].pos;
                array[indexNow].numText.setEndingPoint(array[indexNow].pos.x, array[indexNow].pos.y);
                array[indexNow].phase = 2;


                step++;
                return;

            case 2:
                if(array[indexNow].numText.isMoving) {
                    return;
                }
                array[indexNow].setState(normalSquareState, 2000);
                array[indexNow+1].setState(normalSquareState, 2000);
                array[indexNow].phase = 0;
                indexNow++;
                step++;
                return;

        }
    }

    if(indexNow == arraySize-1){
        switch (array[indexNow].phase){
            case 0:
                code.deHighlightAll();
                code.setHighlight(2);

                array[arraySize - 1].setState(redSquareState, 2000);

                array[arraySize - 1].phase = 1;
                step++;
                return;

            case 1:
                code.deHighlightAll();
                code.setHighlight(2);

                array[arraySize - 1].setValue(0);
                array[arraySize - 1].setNull(true);

                array[arraySize - 1].setState(normalSquareState, 2000);

                array[arraySize - 1].phase = 0;
                isDeleting = false;
                step++;
                return;
        }
    }
}

void DynamicArray::updateDeleteElementImmediately() {
    if (!isDeleting) {
        return;
    }
    if (indexNow < arraySize - 1) {
        switch (array[indexNow].phase){
            case 0:
                code.deHighlightAll();
                code.setHighlight(0);

                array[indexNow].setStateImmediately(highlightedSquareState);
                array[indexNow+1].setStateImmediately(greenSquareState);
                array[indexNow].phase = 1;

                step++;
                return;
            case 1:
                code.deHighlightAll();
                code.setHighlight(1);

                array[indexNow].setValue(array[indexNow+1].getValue());
                array[indexNow].setNull(false);
                array[indexNow].phase = 2;

                step++;
                return;

            case 2:

                array[indexNow].setStateImmediately(normalSquareState);
                array[indexNow+1].setStateImmediately(normalSquareState);
                array[indexNow].phase = 0;
                indexNow++;
                step++;
                return;

        }
    }

    if(indexNow == arraySize-1){
        switch (array[indexNow].phase){
            case 0:
                code.deHighlightAll();
                code.setHighlight(2);

                array[arraySize - 1].setStateImmediately(redSquareState);

                array[arraySize - 1].phase = 1;
                step++;
                return;

            case 1:
                code.deHighlightAll();
                code.setHighlight(2);

                array[arraySize - 1].setValue(0);
                array[arraySize - 1].setNull(true);

                array[arraySize - 1].setStateImmediately(normalSquareState);

                array[arraySize - 1].phase = 0;
                isDeleting = false;
                step++;
                return;
        }
    }
}

void DynamicArray::deleteHead() {
    deleteElement(0);
}

void DynamicArray::deleteTail() {
    deleteElement(arraySize - 1);
}

void DynamicArray::allocate(int sz) {
    deleteArray();
    if(sz > 9){
        alertBox.setMessage("Warning: The input is too long, only the first 9 numbers will be used.");
        alertBox.setEnabled(true);
    }
    for (int i = 0; i < sz; i++) {
        array.emplace_back(0, i, sf::Vector2f(-100, -100), true);
        array[i].setEndingPoint(arrayPos.x + i * offset, arrayPos.y);
    }
    code.setText({
        "array = new int[" + std::to_string(sz) + "];"
    });
    code.deHighlightAll();
    code.setHighlight(0);
}

void DynamicArray::pause() {
    isPausing = true;
}

void DynamicArray::resume() {
    isPausing = false;
}

void DynamicArray::fastForward() {
    if(!(isSearching || isInserting || isDeleting || isUpdatingElement)){
        return;
    }

    moveToStep(step);
    isPausing = false;

    if(isSearching){
        updateSearch();
    }
    if(isInserting){
        updateInsert();
    }
    if(isDeleting){
        updateDeleteElement();
    }
    if(isUpdatingElement){
        updateUpdateElement();
    }

    isPausing = true;
}

void DynamicArray::rewind() {
    if(!(isSearching || isInserting || isDeleting || isUpdatingElement)){
        return;
    }

    moveToStep(step - 2);
    isPausing = false;

    if(isSearching){
        updateSearch();
    }
    if(isInserting){
        updateInsert();
    }
    if(isDeleting){
        updateDeleteElement();
    }
    if(isUpdatingElement){
        updateUpdateElement();
    }

    isPausing = true;
}

void DynamicArray::moveToStep(int targetStep) {
    if(targetStep < 0) {
        targetStep = 0;
    }
    if(isSearching){
        loadArrayState();
        search(searchTarget);
        while (step < targetStep && isSearching) {
            updateSearchImmediately();
        }
    }
    if(isInserting){
        loadArrayState();
        deleteNewArray();
        insert(targetIndex, targetValue);
        while (step < targetStep && isInserting) {
            updateInsertImmediately();
        }
    }
    if(isDeleting){
        loadArrayState();
        deleteElement(targetIndex);
        while (step < targetStep && isDeleting) {
            updateDeleteElementImmediately();
        }
    }
    if(isUpdatingElement){
        loadArrayState();
        updateElement(targetIndex, targetValue);
        while (step < targetStep && isUpdatingElement) {
            updateUpdateElementImmediately();
        }
    }
}


