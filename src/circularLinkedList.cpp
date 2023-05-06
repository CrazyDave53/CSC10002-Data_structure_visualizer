#include "circularLinkedList.h"

CircularLinkedList::CircularLinkedList() :
    LinkedList()
{

}

void CircularLinkedList::update() {
    LinkedList::update();
}

void CircularLinkedList::draw(sf::RenderWindow& window) {
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

    if(isSearching || isInserting || isInsertingHead || isInsertingTail || isDeletingHead || isDeletingTail || isDeletingArbitrary || isUpdating){
        sf::Vector2f pos = sf::Vector2f(1920 - 100, 1080 - 100) - code.getSize();
        code.setPosition(pos.x, pos.y);
        code.draw(window);
    }

    alertBox.draw(window);
    if(head != nullptr && tail != nullptr)
        drawArrow(window, tail->pos + sf::Vector2f (tail->getSize().x/2.0f, 0 ), head->pos - sf::Vector2f (0, head->getSize().y/2.0f), 5.f, 15.f);
}

void CircularLinkedList::drawArrow(sf::RenderWindow& window, sf::Vector2f startPoint, sf::Vector2f endPoint, float arrowThickness, float triangleSize)
{
    float height = fmin(endPoint.y - 20, 60);

    sf::RectangleShape bottomRect(sf::Vector2f(height, arrowThickness));
    bottomRect.setPosition(startPoint.x, startPoint.y - arrowThickness/2.f);
    bottomRect.setFillColor(sf::Color::White);

    sf::RectangleShape rightRect(sf::Vector2f(arrowThickness, startPoint.y - height));
    rightRect.setPosition(startPoint.x + height - arrowThickness, height);
    rightRect.setFillColor(sf::Color::White);

    sf::RectangleShape topRect(sf::Vector2f((startPoint.x - endPoint.x + height), arrowThickness));
    topRect.setPosition(endPoint.x, height);
    topRect.setFillColor(sf::Color::White);

    sf::RectangleShape leftRect(sf::Vector2f(arrowThickness, endPoint.y - height - triangleSize));
    leftRect.setPosition(endPoint.x - arrowThickness/2.f, height);
    leftRect.setFillColor(sf::Color::White);


    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(1, sf::Vector2f(endPoint.x - triangleSize / 2.f, endPoint.y - triangleSize));
    triangle.setPoint(2, sf::Vector2f(endPoint.x + triangleSize / 2.f, endPoint.y - triangleSize));
    triangle.setPoint(0, sf::Vector2f(endPoint.x, endPoint.y));
    triangle.setFillColor(sf::Color::White);

    window.draw(topRect);
    window.draw(leftRect);
    window.draw(rightRect);
    window.draw(bottomRect);
    window.draw(triangle);
}

void CircularLinkedList::search(int target) {
    LinkedList::search(target);
    code.setText({
        "if empty, return NOT_FOUND",
        "index = 0, cur = head",
        "do",
        "   if(cur.value == target)",
        "       return index",
        "   cur = cur.next, index++",
        "while(cur != head)",
        "return NOT_FOUND"
    });
    cur->setState(highlighted, 2000);
    code.setHighlight(0);
    code.setHighlight(1);
}

void CircularLinkedList::updateSearch() {
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
    switch(cur->phase){
        case 0:
            if(cur->isFading) {
                return;
            }
            code.deHighlightAll();
            code.setHighlight(3);
            if(cur->number == searchTarget){
                cur->setState(green, 2000);
                cur->phase = 1;
            }
            else{
                cur->setState(red, 2000);
                cur->phase = 2;
            }

            step++;
            break;
        case 1:
            if(cur->isFading) {
                return;
            }
            code.deHighlightAll();
            code.setHighlight(4);
            cur->phase = 0;
            cur->setState(normal, 2000);
            cur = nullptr;
            head->setState(normal, 2000);
            step++;
            break;
        case 2:
            if(cur->isFading) {
                return;
            }
            code.deHighlightAll();
            code.setHighlight(5);
            cur->phase = 3;
            cur->setState(normal, 2000);
            step++;
            break;
        case 3:
            if(cur->isFading) {
                return;
            }
            code.deHighlightAll();
            code.setHighlight(6);
            if(cur->next == nullptr){
                cur->phase = 4;
                cur->setState(normal, 2000);
            }
            else{
                cur->phase = 0;
                cur->setState(normal, 10000);
                cur = cur->next;
                cur->setState(highlighted, 2000);
            }
            step++;
            break;
        case 4:
            if(cur->isFading) {
                return;
            }
            code.deHighlightAll();
            code.setHighlight(7);
            cur->phase = 5;
            cur->setState(normal, 2000);
            step++;
            break;
        case 5:
            if(cur->isFading) {
                return;
            }
            cur->phase = 0;
            cur->setState(normal, 2000);
            cur = nullptr;
            head->setState(normal, 2000);
            step++;
            break;
    }
}

void CircularLinkedList::updateSearchImmediately() {
    if(cur == nullptr){
        isSearching = false;
        return;
    }
    switch(cur->phase){
        case 0:
            if(cur->number == searchTarget){
                cur->setStateImmediately(green);
                cur->phase = 1;
            }
            else{
                cur->setStateImmediately(red);
                cur->phase = 2;
            }
            step++;
            break;
        case 1:
            cur->phase = 0;
            cur->setStateImmediately(normal);
            cur = nullptr;
            head->setStateImmediately(normal);
            step++;
            break;
        case 2:
            cur->phase = 3;
            cur->setStateImmediately(normal);
            step++;
            break;
        case 3:
            if(cur->next == nullptr){
                cur->phase = 4;
                cur->setStateImmediately(normal);
            }
            else{
                cur->phase = 0;
                cur->setStateImmediately(normal);
                cur = cur->next;
                cur->setStateImmediately(highlighted);
            }
            step++;
            break;
        case 4:
            cur->phase = 5;
            cur->setStateImmediately(normal);
            step++;
            break;
        case 5:
            cur->phase = 0;
            cur->setStateImmediately(normal);
            cur = nullptr;
            head->setStateImmediately(normal);
            step++;
            break;

    }
}



void CircularLinkedList::insertToHead(int value) {
    LinkedList::insertToHead(value);

    code.setText({
        "Node ins = new Node(v)",
        "ins.next = head, tail.next = ins",
        "head = ins"
    });
    code.setHighlight(0);
}

void CircularLinkedList::insertToTail(int value) {
    LinkedList::insertToTail(value);

    code.setText({
        "Node ins = new Node(v)",
        "tail.next = ins, ins.next = head",
        "tail = ins"
    });
    code.setHighlight(0);
}

void CircularLinkedList::deleteHead() {
    LinkedList::deleteHead();
    code.setText({
                         "Node del = head",
                         "head = head.next, tail.next = head",
                         "delete del"
                 });
    code.deHighlightAll();
    code.setHighlight(0);
}

void CircularLinkedList::deleteTail() {
    LinkedList::deleteTail();
    code.setText({
                         "pre = head, del = head.next",
                         "while (del.next != head)",
                         "  pre = pre.next",
                         "pre.next = nullptr",
                         "delete del, tail = pre, tail.next = head"
                 });

    code.deHighlightAll();
    code.setHighlight(0);

}






