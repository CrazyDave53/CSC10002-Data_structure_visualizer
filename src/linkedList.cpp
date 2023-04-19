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
        indexNow(),
        phase()
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

void LinkedList::draw(sf::RenderWindow& window) {
    update();
    node *cur = head;
    while(cur != nullptr){
        cur->draw(window);
        cur = cur->next;
    }
//    if(insertNode != nullptr)
//        insertNode->draw(window);
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
    if(isInserting)
        updateArbitraryInsert();
    node *pt = head;
    while(pt != nullptr){
        pt->update();
//        std::cout<<cur->number<<" ";
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

void LinkedList::search(int m_target) {
    cur = head;
    searchTarget = m_target;
    isSearching = true;
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
    node* pt = new node(value, 100, 200 + 215);
    std::cout<<head<<" "<<pt->next<<"\n";
    pt->next = head;
    head = pt;
    size++;
    updateNodePos(100, 200, 215);
    update();
}

void LinkedList::insertToTail(int value) {
    node* cur = new node(value, tail->pos.x, tail->pos.y + 215);
    tail->next = cur;
    tail = cur;
    size++;
    updateNodePos(100, 200, 215);
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
            insertNode->appear();
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
            std::cout<<preInsert->arrow.isMoving<<" "<<insertNode->arrow.isMoving<<"\n";
            if(preInsert->arrow.isMoving || insertNode->arrow.isMoving)
                return;
            updateNodePos(100, 200, 215);
            preInsert->setState(normal, 2000);
            afterInsert->setState(normal, 2000);
            isInserting = false;
            preInsert->phase = 0;
            preInsert = head;
            indexNow = 0;
            break;

    }
}
