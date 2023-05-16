#include "displaySelectingMenu.h"

displaySelectingMenu::displaySelectingMenu(sf::RenderWindow& window):
    menu(window),
    nextWindow(selectingMenuWindow),
    linkedList(),
    doublyLinkedList(),
    circularLinkedList(),
    stack(),
    queue(),
    staticArray(),
    dynamicArray(),
    bg()

{
    menu.setPosition(30,100);

    layout1 = menu.addHBoxLayout();
    layout2 = menu.addHBoxLayout();

    linkedListTexture.loadFromFile("./assets/textures/LinkedListCard.png");
    doublyLinkedListTexture.loadFromFile("./assets/textures/DoublyLinkedListCard.png");
    circularLinkedListTexture.loadFromFile("./assets/textures/CircularLinkedListCard.png");
    stackTexture.loadFromFile("./assets/textures/StackCard.png");
    queueTexture.loadFromFile("./assets/textures/QueueCard.png");
    staticArrayTexture.loadFromFile("./assets/textures/StaticArrayCard.png");
    dynamicArrayTexture.loadFromFile("./assets/textures/DynamicArrayCard.png");

    linkedList = new gui::SpriteButton(linkedListTexture);
    doublyLinkedList = new gui::SpriteButton(doublyLinkedListTexture);
    circularLinkedList = new gui::SpriteButton(circularLinkedListTexture);
    stack = new gui::SpriteButton(stackTexture);
    queue = new gui::SpriteButton(queueTexture);
    staticArray = new gui::SpriteButton(staticArrayTexture);
    dynamicArray = new gui::SpriteButton(dynamicArrayTexture);

    linkedList->setCallback([&](){
        nextWindow = singlyLinkedListWindow;
    });
    doublyLinkedList->setCallback([&](){
        nextWindow = doublyLinkedListWindow;
    });
    circularLinkedList->setCallback([&](){
        nextWindow = circularLinkedListWindow;
    });
    stack->setCallback([&](){
        nextWindow = stackWindow;
    });
    queue->setCallback([&](){
        nextWindow = queueWindow;
    });
    staticArray->setCallback([&](){
        nextWindow = staticArrayWindow;
    });
    dynamicArray->setCallback([&](){
        nextWindow = dynamicArrayWindow;
    });

    layout1->add(linkedList);
    layout1->add(doublyLinkedList);
    layout1->add(circularLinkedList);
    layout1->add(stack);
    layout1->add(queue);
    layout1->add(staticArray);
    layout1->add(dynamicArray);

    TitleTexture.loadFromFile("./assets/textures/Select.png");
    TitleSprite.setTexture(TitleTexture);
    TitleSprite.setOrigin(TitleTexture.getSize().x/2, TitleTexture.getSize().y/2);
    TitleSprite.setPosition(1920/2, 150);
}

displaySelectingMenu::~displaySelectingMenu(){

}

windowType displaySelectingMenu::mainloop(sf::RenderWindow& window){
    nextWindow = selectingMenuWindow;
    while(window.isOpen() && nextWindow == selectingMenuWindow){
        sf::Event event;
        while(window.pollEvent(event)){
            menu.onEvent(event);
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        menu.setPosition(sf::Vector2f(200 - mousePos.x * 0.3, 350));
        window.clear(sf::Color::Black);
        bg.draw(window);
        window.draw(menu);
        window.draw(TitleSprite);
        window.display();
    }
    return nextWindow;
}