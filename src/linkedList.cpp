#include "linkedList.h"
#include "thread"
#include "time.h"
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
        code(),
        step(),
        isPausing(),
        list()
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

void LinkedList::saveListState() {
    node* pt = head;
    list.clear();
    while(pt != nullptr){
        list.push_back(pt->number);
        pt = pt->next;
    }
}

void LinkedList::loadListState() {
    deleteList();
    if(insertNode != nullptr)
        delete insertNode;

    insertNode = nullptr;

    if(list.empty())
        return;
    head = new node(list[0], 100, 200);
    head->setEndingPoint(100, 200);
    node* cur = head;
    for (int i = 1; i < list.size(); ++i) {
        cur->next = new node(list[i],  100 + i*215, 200);
        cur = cur->next;
    }
    size = list.size();
    std::cout << "load list state" << std::endl;
    std::cout << "size = " << size << std::endl;
    updatePrev();
    refreshList();
    updateArrow();
}

void LinkedList::createList(std::vector<int> v) {
    deleteList();
    if(v.empty())
        return;
    head = new node(v[0], 0, -100);
    head->setEndingPoint(100, 200);
    node* cur = head;
    for (int i = 1; i < v.size(); ++i) {
        cur->next = new node(v[i],  i*215, -100);
        cur = cur->next;
        cur->setEndingPoint(100 + i*215, 200);
    }
    size = v.size();
    update();
}

void LinkedList::refreshList() {
    node *cur = head;
    while(cur != nullptr){
        cur->setStateImmediately(normal);
        cur->phase = 0;
        cur = cur->next;
    }
}

void LinkedList::refreshListPos() {
    node *cur = head;
    for (int i = 0; (cur != nullptr); ++i) {
        cur->setPosition(100 + i*215, 200);
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

    if(isSearching || isInserting || isInsertingHead || isInsertingTail || isDeletingHead || isDeletingTail || isDeletingArbitrary){
        sf::Vector2f pos = sf::Vector2f(1920 - 100, 1080 - 100) - code.getSize();
        code.setPosition(pos.x, pos.y);
        code.draw(window);
    }

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
    if(!isPausing){
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
    }
    if(!(isSearching || isInserting || isInsertingHead || isInsertingTail || isDeletingHead || isDeletingTail || isDeletingArbitrary))
        refreshList();

    updatePrev();
}

void LinkedList::updatePrev() {
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
        pt->clearText();
        if (pt == head)
            pt->concatText("Head");
        if (pt == tail)
            pt->concatText("Tail");
        if (pt == cur)
            pt->concatText("cur");
        if (pt == preInsert)
            pt->concatText("pre");
        if (pt == afterInsert)
            pt->concatText("aft");
        if (pt == deletedNode)
            pt->concatText("del");
        if (pt == insertNode)
            pt->concatText("ins");
        pt->centerText();
        pt = pt->next;
    }
}

bool LinkedList::isArrowMoving() {
    node *pt = head;
    while(pt != nullptr){
        if(pt->arrow.isMoving)
            return true;
        pt = pt->next;
    }
    return false;
}

void LinkedList::search(int m_target) {
    saveListState();
    isPausing = false;

    cur = head;
    searchTarget = m_target;
    isSearching = true;
    code.setText({
                         "if empty, return NOT_FOUND",
                         "index = 0, cur = head",
                         "while(!cur)",
                         "   if(cur.value == target)",
                         "       return index",
                         "   cur = cur.next, index++",
                         "return NOT_FOUND"
                 });
    code.setHighlight(0);
    code.setHighlight(1);
    head->setState(normal, 2000);
    step = 0;
}

void LinkedList::updateSearch() {
//    Phase 0: Highlight the node
//    Phase 1: Check if the node is searchTarget
//    Phase 2: If the node is searchTarget, make it green then return
//    Phase 3: If the node is not, make it red
//    Phase 4: Reinit some values that got touch
    if(cur == nullptr){
        if(head->isFading)
            return;
        isSearching = false;
        return;
    }
    std::cout << "Step: " << step << "Phase: " << cur->phase <<' '<<head->isFading<<' '<<cur<<' '<<head<<std::endl;
    switch(cur->phase){
        case 0:
            if(head->isFading)
                return;
            cur->setState(highlighted,2000);
            cur->phase = 1;
            code.deHighlightAll();
            code.setHighlight(2);
            step++;
            break;
        case 1:
            if(cur->isFading)
                return;
            code.deHighlightAll();
            code.setHighlight(3);
            if(cur->number == searchTarget){
                cur->setState(green,2000);
                cur->phase = 2;
            }
            else{
                cur->setState(red,2000);
                cur->phase = 3;
            }
            step++;
            break;
        case 2:
            if(cur->isFading)
                return;
            cur->phase = 0;
            cur->setState(normal, 10000);
            cur = nullptr;
            head->setState(normal, 10000);
            code.deHighlightAll();
            code.setHighlight(4);
            step++;
            break;
        case 3:
            if(cur->isFading)
                return;
            code.deHighlightAll();
            code.setHighlight(5);
            cur->setState(normal,2000);
            cur->phase = 4;
            step++;
            break;
        case 4:
            if(cur->isFading)
                return;
            cur->phase = 0;
            cur = cur->next;
            if(cur == nullptr) {
                head->setState(normal, 10000);
                code.deHighlightAll();
                code.setHighlight(6);
            }
            else
                head->setState(normal, 2000);
            step++;
            break;
    }
}

void LinkedList::updateSearchImmediately() {
    if(cur == nullptr){
        isSearching = false;
        return;
    }
    switch(cur->phase){
        case 0:
            cur->setStateImmediately(highlighted);
            cur->phase = 1;
            code.deHighlightAll();
            code.setHighlight(2);
            step++;
            break;
        case 1:
            code.deHighlightAll();
            code.setHighlight(3);
            if(cur->number == searchTarget){
                cur->setStateImmediately(green);
                cur->phase = 2;
            }
            else{
                cur->setStateImmediately(red);
                cur->phase = 3;
            }
            step++;
            break;
        case 2:
            cur->phase = 0;
            cur->setStateImmediately(normal);
            cur = nullptr;
            head->setStateImmediately(normal);
            code.deHighlightAll();
            code.setHighlight(4);
            step++;
            break;
        case 3:
            code.deHighlightAll();
            code.setHighlight(5);
            cur->setStateImmediately(normal);
            cur->phase = 4;
            step++;
            break;
        case 4:
            cur->phase = 0;
            cur = cur->next;
            if(cur == nullptr) {
                head->setStateImmediately(normal);
                code.deHighlightAll();
                code.setHighlight(6);
            }
            else
                head->setStateImmediately(normal);
            step++;
            break;
    }
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
    saveListState();
    isPausing = false;

    insertValue = value;
    isInsertingHead = true;
    phase = 0;
    code.setText({
        "Node ins = new Node(v)",
        "ins.next = head",
        "head = ins"
    });
    step = 0;
    size++;
}

void LinkedList::updateInsertHead() {
    if(!isInsertingHead)
        return;
    switch (phase){
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);
            insertNode = new node(insertValue, 100, 200 + 215);
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
            updateArrow();
            insertNode->arrow.moveEnd(insertNode->next->inPivot);
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

void LinkedList::updateInsertHeadImmediately() {
    std::cout << "update insert head immediately" << std::endl;
    std::cout << "phase: " << phase << std::endl;
    std::cout << "step: " << step << std::endl;

    if(!isInsertingHead)
        return;
    switch (phase){
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);
            insertNode = new node(insertValue, 100, 200 + 215);
            insertNode->setStateImmediately(green);
            phase = 1;
            step++;
            break;
        case 1:
            code.deHighlightAll();
            code.setHighlight(1);
            insertNode->next = head;
            head = insertNode;
            updateArrow();
            insertNode->arrow.setEnd(insertNode->next->inPivot);
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

void LinkedList::insertToTail(int value) {
    saveListState();
    isPausing = false;

    insertValue = value;
    isInsertingTail = true;
    step = 0;
    code.setText({
        "Node ins = new Node(v)",
        "tail.next = ins",
        "tail = ins"
    });
    phase = 0;
    size++;
}

void LinkedList::updateInsertTail() {
    if(!isInsertingTail)
        return;
    switch (phase){
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);
            insertNode = new node(insertValue, tail->pos.x, 200 + 215);
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
            updateArrow();
            tail->arrow.moveEnd(tail->next->inPivot);
            preInsert = tail;
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

void LinkedList::updateInsertTailImmediately() {
    if(!isInsertingTail)
        return;
    switch (phase){
        case 0:
            code.deHighlightAll();
            code.setHighlight(0);
            insertNode = new node(insertValue, tail->pos.x, 200 + 215);
            insertNode->setStateImmediately(green);
            phase = 1;
            step++;
            break;
        case 1:
            code.deHighlightAll();
            code.setHighlight(1);
            tail->next = insertNode;
            updateArrow();
            tail->arrow.setEnd(tail->next->inPivot);
            preInsert = tail;
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

void LinkedList::insertArbitrary(int value, int index) {
    saveListState();
    isPausing = false;

    if(index<=0 || index>=size)
        return;

    step = 0;
    code.setText({
        "Node pre = head",
        "for(int i=0; i<index-1; i++)",
        "    pre = pre.next",
        "Node aft = pre.next",
        "Node ins = new Node(v)",
        "ins.next = pre.next",
        "pre.next = ins"
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

void LinkedList::updateArbitraryInsert() {
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
            break;
        case 3:
            if(afterInsert->isFading)
                return;
            code.deHighlightAll();
            code.setHighlight(4);
            insertNode = new node(insertValue, afterInsert->pos.x, afterInsert->pos.y + 215);
            insertNode->setStateImmediately(invisible);
            insertNode->setState(normal, 2000);
            preInsert->phase = 4;
            break;
        case 4:
            if(insertNode->isFading)
                return;
            code.deHighlightAll();
            code.setHighlight(5);
            code.setHighlight(6);
            preInsert->next = insertNode;
            insertNode->next = afterInsert;
            updateArrow();
            preInsert->arrow.moveEnd(insertNode->inPivot);
            insertNode->arrow.moveEnd(afterInsert->inPivot);
            preInsert->phase = 5;
            break;
        case 5:
            if(preInsert->arrow.isMoving || insertNode->arrow.isMoving)
                return;
            updateNodePos(100, 200, 215);
            preInsert->setState(normal, 2000);
            afterInsert->setState(normal, 2000);
            isInserting = false;
            insertNode = nullptr;
            preInsert->phase = 0;
            preInsert = nullptr;
            afterInsert = nullptr;
            refreshList();
            indexNow = 0;
            break;

    }
}

void LinkedList::updateArbitraryInsertImmediately() {
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
            insertNode = new node(insertValue, afterInsert->pos.x, afterInsert->pos.y + 215);
            insertNode->setStateImmediately(invisible);
            insertNode->setStateImmediately(normal);
            preInsert->phase = 4;
            step++;
            break;
        case 4:
            code.deHighlightAll();
            code.setHighlight(5);
            code.setHighlight(6);
            preInsert->next = insertNode;
            insertNode->next = afterInsert;
            updateArrow();
            preInsert->arrow.setEnd(insertNode->inPivot);
            insertNode->arrow.setEnd(afterInsert->inPivot);
            insertNode = nullptr;
            preInsert->phase = 5;
            step++;
            break;
        case 5:
            refreshList();
            refreshListPos();
            preInsert->setStateImmediately(normal);
            afterInsert->setStateImmediately(normal);
            isInserting = false;
            insertNode = nullptr;
            preInsert->phase = 0;
            preInsert = nullptr;
            afterInsert = nullptr;
            refreshList();
            indexNow = 0;
            step++;
            break;

    }
}

void LinkedList::deleteHead() {
    if(head == nullptr)
        return;
    deletedNode = head;
    isDeletingHead = true;
    size--;
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
    size--;
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
    size--;
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
            preDelete->phase = 0;
            break;

    }

}

void LinkedList::rewind() {
    if(!(isSearching || isInsertingHead || isInsertingTail || isInserting || isDeletingHead || isDeletingTail || isDeletingArbitrary))
        return;
    moveToStep(step-1);
    isPausing = true;
}

void LinkedList::fastForward() {
    if(!(isSearching || isInsertingHead || isInsertingTail || isInserting || isDeletingHead || isDeletingTail || isDeletingArbitrary))
        return;
    moveToStep(step+1);
    isPausing = true;
}

void LinkedList::pause() {
    isPausing = true;
}

void LinkedList::resume() {
    isPausing = false;
}

void LinkedList::moveToStep(int targetStep) {
    if(targetStep <= 0)
        targetStep = 0;
    if(isSearching){
        loadListState();
        cur = head;
        int target = targetStep;
        step = 0;
        while(step < target && isSearching){
            updateSearchImmediately();
        }
    }
    if(isInsertingHead){
        loadListState();
        phase = 0;
        int target = targetStep;
        step = 0;
        while(step < target && isInsertingHead){
            updateInsertHeadImmediately();
        }
    }
    if(isInsertingTail){
        loadListState();
        phase = 0;
        int target = targetStep;
        step = 0;
        while(step < target && isInsertingTail){
            updateInsertTailImmediately();
        }
    }
    if(isInserting){
        loadListState();
        preInsert = head;
        indexNow = 0;
        phase = 0;
        int target = targetStep;
        step = 0;
        while(step < target && isInserting){
            updateArbitraryInsertImmediately();
        }
    }
    isPausing = true;
}
