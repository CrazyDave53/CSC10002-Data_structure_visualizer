#include "linkedList.h"
#include "thread"
LinkedList::LinkedList() :
        head(),
        tail(),
        cur(),
        size(),
        searchTarget(),
        isSearching(),
        preInsert(),
        afterInsert(),
        insertNode(),
        insertValue(),
        insertIndex(),
        isInserting(),
        isInsertingHead(),
        isInsertingTail(),
        indexNow(),
        phase(),
        deletedNode(),
        isDeletingHead(),
        isDeletingTail(),
        preDelete(),
        isDeletingArbitrary(),
        deleteIndex(),
        code()
{
}

LinkedList::~LinkedList() {
    deleteList();
}

void LinkedList::createRandom(int sz) {
    deleteList();
    if(sz <= 0)
        return;
    head = new node(rand()%100, 0, -100);
    head->setEndingPoint(100, 200);
    node* cur = head;
    for (int i = 1; i < sz; ++i) {
        cur->next = new node(rand()%100,  i*215, -100);
        cur = cur->next;
        cur->setEndingPoint(100 + i*215, 200);
    }
    size = sz;
    update();
}

void LinkedList::refreshList() {
    node *cur = head;
    while(cur != nullptr){
        cur->setState(normal,500);
        cur->phase = 0;
        cur = cur->next;
    }
}

void LinkedList::draw(sf::RenderWindow& window) {
    update();
    node *cur = head;
    while(cur != nullptr){
        cur->draw(window);
        cur = cur->next;
    }
    if(insertNode != nullptr)
        insertNode->draw(window);
    if(deletedNode != nullptr)
        deletedNode->draw(window);
}

void LinkedList::deleteList() {
    while(head != nullptr){
        node* nxt = head->next;
        delete head;
        head = nxt;
    }
    head = nullptr;
    tail = nullptr;
    cur = nullptr;
}

void LinkedList::update() {
    if(isSearching)
        updateSearch();
    if(isInsertingHead)
        updateInsertHead();
    if(isInsertingTail)
        updateInsertTail();
    if(isInserting)
        updateArbitraryInsert();
    if(isDeletingHead)
        updateDeleteHead();
    if(isDeletingTail)
        updateDeleteTail();
    if(isDeletingArbitrary)
        updateDeleteArbitrary();
    node *pt = head;
    node *pre = nullptr;
    updateText();
    while(pt != nullptr){
        pt->update();
        pt->prev = pre;
        if(pt->next == nullptr)
            tail = pt;
        pt = pt->next;
    }
//    std::cout<<"\n";
}

void LinkedList::updateArrow() {
    node *pt = head;
    while(pt != nullptr){
        pt->updateArrow();
        pt = pt->next;
    }
}

void LinkedList::updateText() {
    node *pt = head;
    while (pt != nullptr) {
        if (pt == head)
            pt->setText("head");
        else if (pt == tail)
            pt->setText("tail");
        else
            pt->setText("");
        pt->centerText();
        pt = pt->next;
    }
}

void LinkedList::updateSearch() {
//    Phase 0: Highlight the node
//    Phase 1: Check if the node is searchTarget
//    Phase 2: If the node is searchTarget, make it green then return
//    Phase 3: If the node is not, make it red
//    Phase 4: Reinit some values that got touch
    if(cur == nullptr){
        isSearching = false;
        cur = head;
        return;
    }
    switch(cur->phase){
        case 0:
            cur->setState(highlighted,2000);
            cur->phase = 1;
            break;
        case 1:
            if(cur->isFading)
                return;
            if(cur->number == searchTarget){
                cur->setState(green,2000);
                cur->phase = 2;
            }
            else{
                cur->setState(red,2000);
                cur->phase = 3;
            }
            break;
        case 2:
            if(cur->isFading)
                return;
            isSearching = false;
            cur->setState(normal,2000);
            cur->phase = 0;
            cur = head;
            break;
        case 3:
            if(cur->isFading)
                return;
            cur->phase = 4;
            break;
        case 4:
            cur->setState(normal,2000);
            cur->phase = 0;
            cur = cur->next;
    }
}

void LinkedList::updateSearchImmediately() {
    if(cur == nullptr){
        isSearching = false;
        cur = head;
        return;
    }
    switch(cur->phase){
        case 0:
            cur->setStateImmediately(highlighted);
            cur->phase = 1;
            break;
        case 1:
            if(cur->isFading)
                return;
            if(cur->number == searchTarget){
                cur->setStateImmediately(green);
                cur->phase = 2;
            }
            else{
                cur->setStateImmediately(red);
                cur->phase = 3;
            }
            break;
        case 2:
            if(cur->isFading)
                return;
            isSearching = false;
            cur->setStateImmediately(normal);
            cur->phase = 0;
            cur = head;
            break;
        case 3:
            if(cur->isFading)
                return;
            cur->phase = 4;
            break;
        case 4:
            cur->setStateImmediately(normal);
            cur->phase = 0;
            cur = cur->next;
    }
}

void LinkedList::search(int m_target) {
    cur = head;
    searchTarget = m_target;
    isSearching = true;
    code.setText({
    });
}

void LinkedList::updateNodePos(float x, float y, float offset) {
    node* pt = head;
    while(pt != nullptr){
        if(pt->pos != sf::Vector2f(x, y))
            pt->setEndingPoint(x, y);
        x += offset;
        pt = pt->next;
    }
}

void LinkedList::insertToHead(int value) {
    insertValue = value;
    isInsertingHead = true;
    phase = 0;
}

void LinkedList::updateInsertHead() {
    if(!isInsertingHead)
        return;
    std::cout<<phase<<"\n";
    switch (phase){
        case 0:
            insertNode = new node(insertValue, 100, 200 + 215);
            insertNode->setStateImmediately(invisible);
            insertNode->setState(green, 2000);
            phase = 1;
            break;
        case 1:
            if(insertNode->isFading)
                return;
            insertNode->next = head;
            head = insertNode;
            updateArrow();
            insertNode->arrow.moveEnd(insertNode->next->inPivot);
            phase = 2;
            break;
        case 2:
            if(insertNode->arrow.isMoving)
                return;
            updateNodePos(100, 200, 215);
            head->setState(normal, 2000);
            phase = 3;
            break;
        case 3:
            if(head->isFading)
                return;
            isInsertingHead = false;
            phase = 0;
            break;
    }
}

void LinkedList::insertToTail(int value) {
    insertValue = value;
    isInsertingTail = true;
    phase = 0;
}

void LinkedList::updateInsertTail() {
    if(!isInsertingTail)
        return;
    std::cout<<phase<<"\n";
    switch (phase){
        case 0:
            insertNode = new node(insertValue, tail->pos.x, 200 + 215);
            insertNode->setStateImmediately(invisible);
            insertNode->setState(green, 2000);
            phase = 1;
            break;
        case 1:
            if(insertNode->isFading)
                return;
            tail->next = insertNode;
            updateArrow();
            tail->arrow.moveEnd(tail->next->inPivot);
            tail = insertNode;
            phase = 2;
            break;
        case 2:
            if(insertNode->arrow.isMoving)
                return;
            updateNodePos(100, 200, 215);
            tail->setState(normal, 2000);
            phase = 3;
            break;
        case 3:
            if(tail->isFading)
                return;
            isInsertingTail = false;
            phase = 0;
            break;
    }
}

void LinkedList::insertArbitrary(int value, int index) {
    if(index<=0 || index>=size)
        return;
    insertValue = value;
    insertIndex = index;
    isInserting = true;
    preInsert = head;
    indexNow = 0;
}

void LinkedList::updateArbitraryInsert() {
//    Phase 0: Highlight the node before the insertion point
//    Phase 1: Highlight the node after and before the insertion node
//    Phase 2: Create a node and draw the arrow
//    Phase 3: Move everything to its place

//    Phase 0: Highlight the node that is being check
//    Phase 1: If this is not the node, make it normal, return to phase 0;
//    Phase 2: If done fading, assign to next and return to phase 0

    if(!isInserting)
        return;
    switch (preInsert->phase) {
        case 0:
            preInsert->setState(highlighted, 2000);
            if(indexNow + 1 == insertIndex)
                preInsert->phase = 2;
            else
                preInsert->phase = 1;
            break;
        case 1:
            if(preInsert->isFading)
                return;
            preInsert->setState(normal, 2000);
            preInsert->phase = 0;
            preInsert = preInsert->next;
            indexNow++;
            break;
        case 2:
            if(preInsert->isFading)
                return;
            preInsert->setState(green, 2000);
            afterInsert = preInsert->next;
            afterInsert->setState(green, 2000);
//            insertNode = new node(insertValue, afterInsert->pos.x, afterInsert->pos.y + 215);
//            preInsert->next = insertNode;
//            insertNode->next = afterInsert;
//            updateNodePos(100, 200, 215);
//            isInserting = false;
            preInsert->phase = 3;
            break;
        case 3:
            insertNode = new node(insertValue, afterInsert->pos.x, afterInsert->pos.y + 215);
            insertNode->setStateImmediately(invisible);
            insertNode->setState(normal, 2000);
            preInsert->phase = 4;
            break;
        case 4:
            if(insertNode->isFading)
                return;
            preInsert->next = insertNode;
            insertNode->next = afterInsert;
            updateArrow();
            preInsert->arrow.moveEnd(insertNode->inPivot);
            insertNode->arrow.moveEnd(afterInsert->inPivot);
            preInsert->phase = 5;
            break;
        case 5:
//            std::cout<<preInsert->arrow.isMoving<<" "<<insertNode->arrow.isMoving<<"\n";
            if(preInsert->arrow.isMoving || insertNode->arrow.isMoving)
                return;
            updateNodePos(100, 200, 215);
            preInsert->setState(normal, 2000);
            afterInsert->setState(normal, 2000);
            isInserting = false;
            insertNode = nullptr;
            preInsert->phase = 0;
            preInsert = head;
            indexNow = 0;
            break;

    }
}

void LinkedList::deleteHead() {
    if(head == nullptr)
        return;

    deletedNode = head;
    isDeletingHead = true;
}

void LinkedList::updateDeleteHead() {
    if(!isDeletingHead)
        return;
    switch (deletedNode->phase) {
        case 0:
            deletedNode->setState(red, 2000);
            head = head->next;
            head->prev = nullptr;
            deletedNode->phase = 1;
            break;
        case 1:
            if(deletedNode->isFading)
                return;
            head->setState(green, 2000);
            deletedNode->phase = 2;
            break;
        case 2:
            if(head->isFading)
                return;
            deletedNode->setState(invisible, 2000);
            deletedNode->phase = 3;
            break;
        case 3:
            if(deletedNode->isFading)
                return;
            delete deletedNode;
            deletedNode = nullptr;
            isDeletingHead = false;
            head->setState(normal, 2000);
            updateNodePos(100, 200, 215);
            break;
    }
}

void LinkedList::deleteTail() {
    if(head == nullptr)
        return;
    if(head->next == nullptr){
        deleteHead();
        return;
    }

    preDelete = nullptr;
    deletedNode = head;
    isDeletingTail = true;
}

void LinkedList::updateDeleteTail() {
    if(!isDeletingTail)
        return;
    switch (deletedNode->phase) {
        case 0:
            deletedNode->setState(highlighted, 2000);
            if(deletedNode->next == nullptr)
                deletedNode->phase = 2;
            else
                deletedNode->phase = 1;
            break;
        case 1:
            if(deletedNode->isFading)
                return;
            deletedNode->setState(normal, 2000);
            deletedNode->phase = 0;
            preDelete = deletedNode;
            deletedNode = deletedNode->next;
            break;
        case 2:
            if(deletedNode->isFading)
                return;
            deletedNode->setState(red, 2000);
            preDelete->next = nullptr;
            tail = preDelete;
            deletedNode->phase = 3;
            break;
        case 3:
            if(deletedNode->isFading)
                return;
            deletedNode->setState(invisible, 2000);
            deletedNode->phase = 4;
            break;
        case 4:
            if(deletedNode->isFading)
                return;
            delete deletedNode;
            deletedNode = nullptr;
            isDeletingTail = false;
            updateNodePos(100, 200, 215);
            break;
    }
}

void LinkedList::deleteArbitrary(int index) {
    if(index<=0 || index>=size-1)
        return;
    deleteIndex = index;
    isDeletingArbitrary = true;
    preDelete = head;
    deletedNode = head->next;
    indexNow = 0;
}

void LinkedList::updateDeleteArbitrary() {
    if (!isDeletingArbitrary)
        return;
    switch (preDelete->phase) {
        case 0:
            preDelete->setState(highlighted, 2000);
            if(indexNow + 1 == deleteIndex)
                preDelete->phase = 2;
            else
                preDelete->phase = 1;
            break;
        case 1:
            if(preDelete->isFading)
                return;
            preDelete->setState(normal, 2000);
            preDelete->phase = 0;
            preDelete = preDelete->next;
            deletedNode = deletedNode->next;
            indexNow++;
            break;
        case 2:
            if(preDelete->isFading)
                return;
            preDelete->setState(green, 2000);
            deletedNode->setState(red, 2000);
            preDelete->phase = 3;
            break;
        case 3:
            if(preDelete->isFading || deletedNode->isFading)
                return;
            deletedNode->setEndingPoint(deletedNode->pos.x, deletedNode->pos.y + 215);
            preDelete->phase = 4;
            break;
        case 4:
            if(deletedNode->isMoving)
                return;
            preDelete->next = deletedNode->next;
            updateArrow();
            preDelete->arrow.moveEnd(deletedNode->next->inPivot);
            deletedNode->setState(invisible, 2000);
            preDelete->phase = 5;
            break;
        case 5:
            if(deletedNode->isFading)
                return;
            delete deletedNode;
            deletedNode = nullptr;
            isDeletingArbitrary = false;
            preDelete->setState(normal, 2000);
            updateNodePos(100, 200, 215);
            size--;
            preDelete->phase = 0;
            break;

    }

}
