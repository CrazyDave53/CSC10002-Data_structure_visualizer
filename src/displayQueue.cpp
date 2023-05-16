#include "displayQueue.h"
#include <iostream>
#include <string>
displayQueue::displayQueue(sf::RenderWindow &window):
        menu(window),
        nextWindow(singlyLinkedListWindow),
        mediaBar(menu),
        createMenu(menu, "Create"),
        seekMenu(menu, "Seek"),
        addMenu(menu, "Add"),
        removeMenu(menu, "Remove"),
        clearMenu(menu, "Clear"),

        queue(),
        buttonBG(),

        createRandomFrame(),
        createRandom(),
        createFrame(),
        inputCreate(),
        goCreate(),

        createFromFileFrame(),
        createFromFile(),

        createUserInputFrame(),
        createUserInput(),

        inputSearchValue(),
        goSearch(),

        inputAddValue(),
        goAdd(),

        insertHead(),
        insertTail(),
        insertArbitrary(),
        inputInsertValue(),
        inputInsertIndex(),
        insertHeadFrame(),
        insertTailFrame(),
        insertArbitraryFrame(),
        insertFrame(),
        goInsert(),

        deleteHead(),
        deleteTail(),
        deleteArbitrary(),
        inputDeleteIndex(),
        inputDeleteValue(),
        deleteHeadFrame(),
        deleteTailFrame(),
        deleteArbitraryFrame(),
        deleteFrame(),
        goDelete(),

        bg(),
        changeWindow(),
        backToMenu()
{
    menu.setPosition(100,600);
    buttonBG.loadFromFile("./assets/button/newbutton.png");
    createMenu.mainButton->setCallback([this]{
        createMenu.deleteFrame();
        //init null
        createRandomFrame = nullptr;
        createRandom = nullptr;
        createFrame = nullptr;
        goCreate = nullptr;
        inputCreate = nullptr;
        createUserInputFrame = nullptr;
        createUserInput = nullptr;
        inputCreate = nullptr;

        createMenu.frame = createMenu.mainframe->addHBoxLayout();

        createRandomFrame = createMenu.frame->addVBoxLayout();
        createRandom = new gui::SpriteButton(buttonBG,"Random");
        createRandomFrame->add(createRandom);

        createFromFileFrame = createMenu.frame->addVBoxLayout();
        createFromFile = new gui::SpriteButton(buttonBG,"From File");
        createFromFileFrame->add(createFromFile);

        createUserInputFrame = createMenu.frame->addVBoxLayout();
        createUserInput = new gui::SpriteButton(buttonBG,"User Input");
        createUserInputFrame->add(createUserInput);

        //Set callback
        createRandom->setCallback([this]{
            if(createRandomFrame->m_last == createFrame){
                createRandomFrame->removeLast();//remove createFrame
            }
            if(createUserInputFrame->m_last == createFrame){
                createUserInputFrame->removeLast();//remove createFrame
            }
            if(createFromFileFrame->m_last == createFrame){
                createFromFileFrame->removeLast();//remove createFrame
            }

            createFrame = nullptr;
            inputCreate = nullptr;
            goCreate = nullptr;

            createFrame = createRandomFrame->addHBoxLayout();
            inputCreate = new gui::TextBox(100);
            inputCreate->setMaxLength(1);
            inputCreate->setPlaceholder("Input size");
            createFrame->add(inputCreate);
            goCreate = createFrame->addButton("GO", [this]{
                if(!inputCreate->getText().toAnsiString().empty()){
                    try{
                        queue.createRandom(std::stoi(inputCreate->getText().toAnsiString()));
                    }
                    catch(std::invalid_argument& e){
                        //do nothing
                    }
                }
            });
        });
        createFromFile->setCallback([this]{
            if(createRandomFrame->m_last == createFrame){
                createRandomFrame->removeLast();//remove createFrame
            }
            if(createUserInputFrame->m_last == createFrame){
                createUserInputFrame->removeLast();//remove createFrame
            }
            if(createFromFileFrame->m_last == createFrame){
                createFromFileFrame->removeLast();//remove createFrame
            }
            createFrame = nullptr;
            inputCreate = nullptr;
            goCreate = nullptr;

            createFrame = createFromFileFrame->addHBoxLayout();
            goCreate = createFrame->addButton("      Browse      ", [this]{
                queue.createFromFile();
            });

        });
        createUserInput->setCallback([this]{
            if(createRandomFrame->m_last == createFrame){
                createRandomFrame->removeLast();//remove createFrame
            }
            if(createUserInputFrame->m_last == createFrame){
                createUserInputFrame->removeLast();//remove createFrame
            }
            if(createFromFileFrame->m_last == createFrame){
                createFromFileFrame->removeLast();//remove createFrame
            }
            createFrame = nullptr;
            inputCreate = nullptr;
            goCreate = nullptr;

            createFrame = createUserInputFrame->addHBoxLayout();
            inputCreate = new gui::TextBox(300);
            inputCreate->setMaxLength(300);
            inputCreate->setPlaceholder("e.g. 1,3,4,6,22,15,47,32");
            createFrame->add(inputCreate);
            goCreate = createFrame->addButton("GO", [this]{
                if(!inputCreate->getText().toAnsiString().empty())
                    queue.createUserInput(inputCreate->getText().toAnsiString());
            });
        });

    });
    seekMenu.mainButton->setCallback([this]{
        queue.seek();
    });
    addMenu.mainButton->setCallback([this]{
        addMenu.deleteFrame();
        //init
        addMenu.frame = nullptr;
        inputAddValue = nullptr;
        goAdd = nullptr;

        addMenu.frame = addMenu.mainframe->addHBoxLayout();
        inputAddValue = new gui::TextBox(80);
        inputAddValue->setMaxLength(2);
        inputAddValue->setPlaceholder("Value");
        addMenu.frame->add(inputAddValue);
        goAdd = addMenu.frame->addButton("GO", [this]{
            if(!inputAddValue->getText().toAnsiString().empty()){
                try{
                    queue.insertToTail(std::stoi(inputAddValue->getText().toAnsiString()));
                }catch(std::invalid_argument){
                    //do nothing
                }
            }
        });
    });
    removeMenu.mainButton->setCallback([this]{
        queue.deleteHead();
    });
    clearMenu.mainButton->setCallback([this]{
        queue.clear();
    });

    mediaBar.m_forwardButton->setCallback([this]{
        queue.fastForward();
    });
    mediaBar.m_backwardButton->setCallback([this]{
        queue.rewind();
    });
    mediaBar.m_playButton->setCallback([this]{
        if(queue.isPausing)
            queue.resume();
        else
            queue.pause();
    });

    changeWindow = new gui::OptionsBox<windowType>();
    changeWindow->addItem("Singly Linked List",singlyLinkedListWindow);
    changeWindow->addItem("Doubly Linked List",doublyLinkedListWindow);
    changeWindow->addItem("Circular Linked List",circularLinkedListWindow);
    changeWindow->addItem("Stack",stackWindow);
    changeWindow->addItem("Queue",queueWindow);
    changeWindow->addItem("Static Array",staticArrayWindow);
    changeWindow->addItem("Dynamic Array",dynamicArrayWindow);

    changeWindow->selectItem(4);
    changeWindow->setCallback([this](){
        nextWindow = changeWindow->getSelectedValue();
    });

    menu.add(changeWindow);
    changeWindow->setPosition(sf::Vector2f {10,10});

    backToMenu = new gui::SpriteButton(buttonBG, "Back to Menu");
    backToMenu->setCallback([this]{
        nextWindow = mainMenuWindow;
    });
    menu.add(backToMenu);
    backToMenu->setPosition(sf::Vector2f {1700,10} - menu.getPosition());



//    mediaBar.m_backwardButton->setPosition(sf::Vector2f {860,1000} - mediaBar.m_mediaBar->getPosition() - menu.getPosition());
//    mediaBar.m_playButton->setPosition(sf::Vector2f {960,1000} - mediaBar.m_mediaBar->getPosition() - menu.getPosition());
//    mediaBar.m_forwardButton->setPosition(sf::Vector2f {1060,1000} - mediaBar.m_mediaBar->getPosition() - menu.getPosition());


}

displayQueue::~displayQueue() {

}

windowType displayQueue::mainloop(sf::RenderWindow &window) {
    nextWindow = singlyLinkedListWindow;
    changeWindow->selectItem(4);
    while (window.isOpen() && nextWindow == singlyLinkedListWindow)
    {
        sf::Event event;


        while (window.pollEvent(event))
        {
            // Send events to menu
            menu.onEvent(event);
            queue.onEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
//        std::cout << createMenu.frame << "\n";
        // Clear screen
        if(!createMenu.mainframe->isFocused()){
            createMenu.deleteFrame();
            createMenu.mainframe->recomputeGeometry();
//            menu.recomputeGeometry();
        }
        if(!seekMenu.mainframe->isFocused()){
            seekMenu.deleteFrame();
            seekMenu.mainframe->recomputeGeometry();
//            menu.recomputeGeometry();
        }
        if(!addMenu.mainframe->isFocused()){
            addMenu.deleteFrame();
            addMenu.mainframe->recomputeGeometry();
        }
        if(!removeMenu.mainframe->isFocused()){
            removeMenu.deleteFrame();
            removeMenu.mainframe->recomputeGeometry();
//            menu.recomputeGeometry();
        }
        if(!clearMenu.mainframe->isFocused()){
            clearMenu.deleteFrame();
            clearMenu.mainframe->recomputeGeometry();
//            menu.recomputeGeometry();
        }

        mediaBar.setPauseState(queue.isPausing);

        mediaBar.m_backwardButton->setPosition(sf::Vector2f {860,1000} - menu.getPosition());
        mediaBar.m_playButton->setPosition(sf::Vector2f {960,1000} - menu.getPosition());
        mediaBar.m_forwardButton->setPosition(sf::Vector2f {1060,1000} - menu.getPosition());
        mediaBar.m_speedSlider->setPosition(sf::Vector2f {100,1000} - menu.getPosition());

        changeWindow->setPosition(sf::Vector2f {10,10} - menu.getPosition());
        backToMenu->setPosition(sf::Vector2f {1750,10} - menu.getPosition());

        window.clear(gui::Theme::windowBgColor);


        bg.draw(window);

        mediaBar.draw(window);
        queue.draw(window);
        window.draw(menu);
        // Update the window
        window.display();
    }
    return nextWindow;
}
