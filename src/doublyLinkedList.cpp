#include "doublyLinkedList.h"

void DoublyLinkedList::createRandom(int sz) {
    deleteList();
    if(sz <= 0)
        return;
    head = new node(rand()%100, 0, -100, true);
    head->setEndingPoint(100, 200);
    node* cur = head;
    for (int i = 1; i < sz; ++i) {
        cur->next = new node(rand()%100,  i*215, -100, true);
        cur = cur->next;
        cur->setEndingPoint(100 + i*215, 200);
    }
    size = sz;
    update();
}

void DoublyLinkedList::createList(std::vector<int> v) {
    deleteList();
    if(v.empty())
        return;
    if(v.size() > 9){
        v.resize(9);
        alertBox.setMessage("Warning: The input is too long, only the first 9 numbers will be used.");
        alertBox.setEnabled(true);
    }
    for(int i = 0; i < v.size(); ++i){
        if(v[i] < 0 || v[i] > 99){
            alertBox.setMessage("Warning: The input contains numbers that are out of range.\nEvery out-of-range number will be set to a random number between 0 and 99.");
            alertBox.setEnabled(true);
            v[i] = rand() % 100;
        }
    }
    head = new node(v[0], 0, -100, true);
    head->setEndingPoint(100, 200);
    node* cur = head;
    for (int i = 1; i < v.size(); ++i) {
        cur->next = new node(v[i],  i*215, -100, true);
        cur = cur->next;
        cur->setEndingPoint(100 + i*215, 200);
    }
    size = v.size();
    update();
}

void DoublyLinkedList::loadListState() {
    deleteList();
    if(insertNode != nullptr)
        delete insertNode;

    insertNode = nullptr;

    if(list.empty())
        return;
    head = new node(list[0], 100, 200, true);
    head->setEndingPoint(100, 200);
    node* cur = head;
    for (int i = 1; i < list.size(); ++i) {
        cur->next = new node(list[i],  100 + i*215, 200, true);
        cur = cur->next;
    }
    size = list.size();
    updatePrev();
    refreshList();
    updateArrow();
    updateText();
}

void DoublyLinkedList::update() {
    node* cur = head;
    while(cur != nullptr){
        cur->isDoubly = true;
        cur = cur->next;
    }
    LinkedList::update();
}

void DoublyLinkedList::insertToHead(int value) {
    if(size >= 9){
        alertBox.setMessage("The list only supports 9 nodes");
        alertBox.setEnabled(true);
        return;
    }
    saveListState();
    isPausing = false;

    insertValue = value;
    isInsertingHead = true;
    phase = 0;
    code.setText({
                         "Node ins = new Node(v)",
                         "ins.next = head, head.prev = ins",
                         "head = ins"
                 });
    step = 0;
    size++;
}

void DoublyLinkedList::updateInsertHead() {
    if(!isInsertingHead)
        return;
    switch (phase){
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);
            insertNode = new node(insertValue, 100, 200 + 215, true);
            insertNode->setStateImmediately(invisible);
            insertNode->setState(green, 2000);
            phase = 1;
            step++;
            break;
        case 1:
            if(insertNode->isFading)
                return;
            code.deHighlightAll();
            code.setHighlight(1);
            insertNode->next = head;
            head = insertNode;
            updatePrev();
            updateArrow();
            if(insertNode->next != nullptr){
                insertNode->arrow.moveEnd(insertNode->next->inPivot);
                insertNode->next->arrowReverse.moveEnd(insertNode->reversedInPivot);
            }
            insertNode = nullptr;
            phase = 2;
            step++;
            break;
        case 2:
            if(isArrowMoving())
                return;
            code.deHighlightAll();
            code.setHighlight(2);
            updateNodePos(100, 200, 215);
            head->setState(normal, 2000);
            phase = 3;
            step++;
            break;
        case 3:
            if(head->isFading)
                return;
            isInsertingHead = false;
            insertNode = nullptr;
            phase = 0;
            step++;
            break;
    }
}

void DoublyLinkedList::updateInsertHeadImmediately() {
    if(!isInsertingHead)
        return;
    switch (phase){
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);
            insertNode = new node(insertValue, 100, 200 + 215, true);
            insertNode->setStateImmediately(green);
            phase = 1;
            step++;
            break;
        case 1:
            code.deHighlightAll();
            code.setHighlight(1);
            insertNode->next = head;
            head = insertNode;
            updatePrev();
            updateArrow();
            insertNode->arrow.setEnd(insertNode->next->inPivot);
            insertNode->next->arrowReverse.setEnd(insertNode->reversedInPivot);
            insertNode = nullptr;
            phase = 2;
            step++;
            break;
        case 2:
            code.deHighlightAll();
            code.setHighlight(2);
            refreshListPos();
            head->setStateImmediately(normal);
            phase = 3;
            step++;
            break;
        case 3:
            isInsertingHead = false;
            insertNode = nullptr;
            phase = 0;
            step++;
            break;
    }
}

void DoublyLinkedList::insertToTail(int value) {
    if(size >= 9){
        alertBox.setMessage("The list only supports 9 nodes");
        alertBox.setEnabled(true);
        return;
    }
    if(tail == nullptr){
        insertToHead(value);
        return;
    }
    saveListState();
    isPausing = false;

    insertValue = value;
    isInsertingTail = true;
    step = 0;
    code.setText({
                         "Node ins = new Node(v)",
                         "tail.next = ins, ins.prev = tail",
                         "tail = ins"
                 });
    phase = 0;
    size++;
}

void DoublyLinkedList::updateInsertTail() {
    if(!isInsertingTail)
        return;
    switch (phase){
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);
            insertNode = new node(insertValue, tail->pos.x, 200 + 215, true);
            insertNode->setStateImmediately(invisible);
            insertNode->setState(green, 2000);
            phase = 1;
            step++;
            break;
        case 1:
            if(insertNode->isFading)
                return;
            code.deHighlightAll();
            code.setHighlight(1);
            tail->next = insertNode;
            insertNode->prev = tail;
            preInsert = tail;
            updatePrev();
            updateArrow();
            preInsert->arrow.moveEnd(insertNode->inPivot);
            insertNode->arrowReverse.moveEnd(preInsert->reversedInPivot);
            tail = insertNode;
            insertNode = nullptr;
            phase = 2;
            step++;
            break;
        case 2:
            if(preInsert->arrow.isMoving)
                return;
            code.deHighlightAll();
            code.setHighlight(2);
            updateNodePos(100, 200, 215);
            tail->setState(normal, 2000);
            phase = 3;
            step++;
            break;
        case 3:
            if(tail->isFading)
                return;
            isInsertingTail = false;
            insertNode = nullptr;
            preInsert = nullptr;
            phase = 0;
            step++;
            break;
    }
}

void DoublyLinkedList::updateInsertTailImmediately() {
    if(!isInsertingTail)
        return;
    switch (phase){
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);
            insertNode = new node(insertValue, tail->pos.x, 200 + 215, true);
            insertNode->setStateImmediately(green);
            phase = 1;
            step++;
            break;
        case 1:
            code.deHighlightAll();
            code.setHighlight(1);
            tail->next = insertNode;
            preInsert = tail;
            updatePrev();
            updateArrow();
            preInsert->arrow.setEnd(insertNode->inPivot);
            insertNode->arrowReverse.setEnd(preInsert->reversedInPivot);
            tail = insertNode;
            insertNode = nullptr;
            phase = 2;
            step++;
            break;
        case 2:
            code.deHighlightAll();
            code.setHighlight(2);
            refreshListPos();
            tail->setStateImmediately(normal);
            phase = 3;
            step++;
            break;
        case 3:
            isInsertingTail = false;
            insertNode = nullptr;
            preInsert = nullptr;
            phase = 0;
            step++;
            break;
    }
}

void DoublyLinkedList::insertArbitrary(int value, int index) {
    if(size >= 9){
        alertBox.setMessage("The list only supports 9 nodes");
        alertBox.setEnabled(true);
        return;
    }
    if(index<0 || index>size){
        alertBox.setMessage("Index out of bound");
        alertBox.setEnabled(true);
        return;
    }
    if(index == 0){
        insertToHead(value);
        return;
    }
    if(index == size){
        insertToTail(value);
        return;
    }

    saveListState();
    isPausing = false;

    step = 0;
    code.setText({
                         "Node pre = head",
                         "for(int i=0; i<index-1; i++)",
                         "    pre = pre.next",
                         "Node aft = pre.next",
                         "Node ins = new Node(v)",
                         "ins.next = pre.next, pre.next = ins",
                         "ins.prev = pre, aft.prev = ins"
                 });
    insertValue = value;
    insertIndex = index;
    isInserting = true;
    preInsert = head;
    indexNow = 0;
    code.deHighlightAll();
    code.setHighlight(0);
    head->setState(highlighted, 2000);
    size++;
}

void DoublyLinkedList::updateArbitraryInsert() {
    if(head->isFading)
        return;
    if(!isInserting)
        return;
    switch (preInsert->phase) {
        case 0:
            if(preInsert->prev && preInsert->prev->isFading)
                return;
            preInsert->setState(highlighted, 2000);
            code.deHighlightAll();
            code.setHighlight(1);
            if(indexNow + 1 == insertIndex)
                preInsert->phase = 2;
            else
                preInsert->phase = 1;
            step++;
            break;
        case 1:
            if(preInsert->isFading)
                return;
            code.deHighlightAll();
            code.setHighlight(2);
            preInsert->setState(normal, 2000);
            preInsert->phase = 0;
            preInsert = preInsert->next;
            indexNow++;
            step++;
            break;
        case 2:
            if(preInsert->isFading)
                return;
            code.deHighlightAll();
            code.setHighlight(3);
            preInsert->setState(green, 2000);
            afterInsert = preInsert->next;
            afterInsert->setState(green, 2000);
            preInsert->phase = 3;
            step++;
            break;
        case 3:
            if(afterInsert->isFading)
                return;
            code.deHighlightAll();
            code.setHighlight(4);
            insertNode = new node(insertValue, afterInsert->pos.x, afterInsert->pos.y + 215, true);
            insertNode->setStateImmediately(invisible);
            insertNode->setState(normal, 2000);
            preInsert->phase = 4;
            step++;
            break;
        case 4:
            if(insertNode->isFading)
                return;
            code.deHighlightAll();
            code.setHighlight(5);
            code.setHighlight(6);
            preInsert->next = insertNode;
            insertNode->next = afterInsert;
            updatePrev();
            updateArrow();
            preInsert->arrow.moveEnd(insertNode->inPivot);
            insertNode->arrow.moveEnd(afterInsert->inPivot);
            insertNode->arrowReverse.moveEnd(preInsert->reversedInPivot);
            afterInsert->arrowReverse.moveEnd(insertNode->reversedInPivot);
            insertNode = nullptr;
            preInsert->phase = 5;
            step++;
            break;
        case 5:
            if(preInsert->arrow.isMoving)
                return;
            updateNodePos(100, 200, 215);
            preInsert->setState(normal, 2000);
            afterInsert->setState(normal, 2000);
            isInserting = false;
            preInsert = nullptr;
            afterInsert = nullptr;
            refreshList();
            indexNow = 0;
            step++;
            break;

    }
}

void DoublyLinkedList::updateArbitraryInsertImmediately() {
    std::cout << "insertNode" << insertNode << std::endl;
    std::cout << "preInsert" << preInsert << std::endl;
    std::cout << "afterInsert" << afterInsert << std::endl;
    if(!isInserting)
        return;
    std::cout << preInsert->phase << std::endl;
    switch (preInsert->phase) {
        case 0:
            preInsert->setStateImmediately(highlighted);
            code.deHighlightAll();
            code.setHighlight(1);
            if(indexNow + 1 == insertIndex)
                preInsert->phase = 2;
            else
                preInsert->phase = 1;
            step++;
            break;
        case 1:
            code.deHighlightAll();
            code.setHighlight(2);
            preInsert->setStateImmediately(normal);
            preInsert->phase = 0;
            preInsert = preInsert->next;
            indexNow++;
            step++;
            break;
        case 2:
            code.deHighlightAll();
            code.setHighlight(3);
            preInsert->setStateImmediately(green);
            afterInsert = preInsert->next;
            afterInsert->setStateImmediately(green);
            preInsert->phase = 3;
            step++;
            break;
        case 3:
            code.deHighlightAll();
            code.setHighlight(4);
            insertNode = new node(insertValue, afterInsert->pos.x, afterInsert->pos.y + 215, true);
            insertNode->setStateImmediately(invisible);
            insertNode->setStateImmediately(normal);
            preInsert->phase = 4;
            step++;
            break;
        case 4:
            code.deHighlightAll();
            code.setHighlight(5);
            preInsert->next = insertNode;
            insertNode->next = afterInsert;
            updatePrev();
            updateArrow();
            preInsert->arrow.setEnd(insertNode->inPivot);
            insertNode->arrow.setEnd(afterInsert->inPivot);
            insertNode->arrowReverse.setEnd(preInsert->reversedInPivot);
            afterInsert->arrowReverse.setEnd(insertNode->reversedInPivot);
            preInsert->phase = 5;

            insertNode = nullptr;
            step++;
            break;
        case 5:
            std::cout << "here" << std::endl;
            refreshList();
            refreshListPos();
            preInsert->setStateImmediately(normal);
            afterInsert->setStateImmediately(normal);
            preInsert->phase = 0;
            isInserting = false;
            insertNode = nullptr;
            preInsert = nullptr;
            afterInsert = nullptr;
            refreshList();
            indexNow = 0;
            step++;
            std::cout << "here" << std::endl;
            break;

    }
}

void DoublyLinkedList::deleteHead() {
    LinkedList::deleteHead();
    code.setText({
         "Node *del = head",
         "head = head.next, head.prev = nullptr",
         "delete del",
     });
}

void DoublyLinkedList::deleteTail() {
    LinkedList::deleteTail();
}

void DoublyLinkedList::deleteArbitrary(int index) {
    LinkedList::deleteArbitrary(index);
    code.setText({
         "pre = head",
         "for (k = 0; k < i-1; k++)",
         "  pre = pre.next",
         "del = pre.next, aft = del.next",
         "pre.next = aft, aft.prev = pre",
         "delete del"
     });
    afterDelete = deletedNode->next;
}

void DoublyLinkedList::updateDeleteArbitrary() {
    if (!isDeletingArbitrary)
        return;
    if (head->isFading)
        return;
    switch (preDelete->phase) {
        case 0:
            if(preDelete != head && preDelete->prev->isFading)
                return;
            preDelete->setState(highlighted, 2000);
            if(indexNow + 1 == deleteIndex)
                preDelete->phase = 2;
            else
                preDelete->phase = 1;

            code.deHighlightAll();
            code.setHighlight(1);
            step++;
            break;
        case 1:
            if(preDelete->isFading)
                return;
            preDelete->setState(normal, 2000);
            preDelete->phase = 0;
            preDelete = preDelete->next;
            deletedNode = preDelete->next;
            afterDelete = deletedNode->next;
            indexNow++;

            code.deHighlightAll();
            code.setHighlight(2);
            step++;
            break;
        case 2:
            if(preDelete->isFading)
                return;
            preDelete->setState(green, 2000);
            deletedNode->setState(red, 2000);
            afterDelete->setState(green, 2000);
            preDelete->phase = 3;

            code.deHighlightAll();
            code.setHighlight(3);
            step++;
            break;
        case 3:
            if(preDelete->isFading || deletedNode->isFading)
                return;
            deletedNode->setEndingPoint(deletedNode->pos.x, deletedNode->pos.y + 215);
            preDelete->phase = 4;

            code.deHighlightAll();
            code.setHighlight(4);
            step++;
            break;
        case 4:
            if(deletedNode->isMoving)
                return;
            preDelete->next = afterDelete;

            deletedNode->next = nullptr;
            deletedNode->prev = nullptr;

            updatePrev();
            updateArrow();
            preDelete->arrow.moveEnd(afterDelete->inPivot);
            afterDelete->arrowReverse.moveEnd(preDelete->reversedInPivot);
            deletedNode->setState(invisible, 2000);
            preDelete->phase = 5;

            code.deHighlightAll();
            code.setHighlight(5);
            step++;
            break;
        case 5:
            if(deletedNode->isFading || preDelete->arrow.isMoving || afterDelete->arrowReverse.isMoving)
                return;
            delete deletedNode;
            deletedNode = nullptr;
            isDeletingArbitrary = false;
            preDelete->setState(normal, 2000);
            updateNodePos(100, 200, 215);
            preDelete->phase = 0;
            preDelete = nullptr;
            afterDelete = nullptr;
            refreshList();
            step++;
            break;
    }
}

void DoublyLinkedList::updateDeleteArbitraryImmediately() {
    if (!isDeletingArbitrary)
        return;
    switch (preDelete->phase) {
        case 0:
            preDelete->setStateImmediately(highlighted);
            if(indexNow + 1 == deleteIndex)
                preDelete->phase = 2;
            else
                preDelete->phase = 1;

            code.deHighlightAll();
            code.setHighlight(1);
            step++;
            break;
        case 1:
            preDelete->setStateImmediately(normal);
            preDelete->phase = 0;
            preDelete = preDelete->next;
            deletedNode = preDelete->next;
            indexNow++;

            code.deHighlightAll();
            code.setHighlight(2);
            step++;
            break;
        case 2:
            preDelete->setStateImmediately(green);
            deletedNode->setStateImmediately(red);
            preDelete->phase = 3;

            code.deHighlightAll();
            code.setHighlight(3);
            step++;
            break;
        case 3:
            deletedNode->setPosition(deletedNode->pos.x, deletedNode->pos.y + 215);
            preDelete->phase = 4;

            code.deHighlightAll();
            code.setHighlight(4);
            step++;
            break;
        case 4:
            preDelete->next = deletedNode->next;
            updateArrow();
            preDelete->arrow.setEnd(deletedNode->next->inPivot);
            deletedNode->setStateImmediately(invisible);
            preDelete->phase = 5;

            code.deHighlightAll();
            code.setHighlight(5);
            step++;
            break;
        case 5:
            delete deletedNode;
            deletedNode = nullptr;
            isDeletingArbitrary = false;
            preDelete->setStateImmediately(normal);
            refreshListPos();
            preDelete->phase = 0;

            step++;
            break;
    }
}


