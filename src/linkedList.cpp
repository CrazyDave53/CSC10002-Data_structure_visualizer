#include "linkedList.h"
#include "thread"
LinkedList::LinkedList() :
    head()
{

}

LinkedList::~LinkedList() {
    deleteList();
}

void LinkedList::createRandom(int size) {
    deleteList();
    if(size < 0)
        return;
    head = new node(rand()%100, 0, -100);
    head->setEndingPoint(100, 200);
    node* cur = head;
    for (int i = 1; i < size; ++i) {
        cur->next = new node(rand()%100,  i*250, -100);
        cur = cur->next;
        cur->setEndingPoint(100 + i*250, 200);
    }
    update();
}

void LinkedList::draw(sf::RenderWindow& window) {
    update();
    node *cur = head;
    while(cur != nullptr){
        cur->draw(window);
        cur = cur->next;
    }
}

void LinkedList::deleteList() {
    while(head != nullptr){
        node* nxt = head->next;
        delete head;
        head = nxt;
    }
    head = nullptr;
}

void LinkedList::update() {
    node *cur = head;
    while(cur != nullptr){
        cur->update();
//        std::cout<<cur->number<<" ";
        cur = cur->next;
    }
//    std::cout<<"\n";
}

void LinkedList::search(int n) {
    pt = head;
}

