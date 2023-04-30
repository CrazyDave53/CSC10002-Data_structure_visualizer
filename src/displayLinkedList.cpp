#include "displayLinkedList.h"
#include <iostream>
#include <string>
displayLinkedList::displayLinkedList(sf::RenderWindow &window):
    menu(window),
    nextWindow(singlyLinkedListWindow),
    mediaBar(menu),
    createMenu(menu, "Create"),
    searchMenu(menu, "Search"),
    updateMenu(menu, "Update"),
    insertMenu(menu, "Insert"),
    deleteMenu(menu, "Delete"),

    linkedList(),
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

    inputUpdateIndex(),
    inputUpdateValue(),
    goUpdate(),

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
                        linkedList.createRandom(std::stoi(inputCreate->getText().toAnsiString()));
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
                linkedList.createFromFile();
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
                    linkedList.createUserInput(inputCreate->getText().toAnsiString());
            });
        });

    });
    searchMenu.mainButton->setCallback([this]{
        searchMenu.deleteFrame();
        //init ptr
        searchMenu.frame = nullptr;

        searchMenu.frame = searchMenu.mainframe->addHBoxLayout();
        inputSearchValue = new gui::TextBox(110);
        inputSearchValue->setMaxLength(2);
        inputSearchValue->setPlaceholder("Search for");
        searchMenu.frame->add(inputSearchValue);;

        goSearch = searchMenu.frame->addButton("GO",[this]{
            if(!inputSearchValue->getText().toAnsiString().empty()){
                try{
                    linkedList.search(std::stoi(inputSearchValue->getText().toAnsiString()));
                }catch(std::invalid_argument){
                    //do nothing
                }
            }
        });
    });
    updateMenu.mainButton->setCallback([this]{
        updateMenu.deleteFrame();
        //init
        updateMenu.frame = nullptr;
        inputUpdateIndex = nullptr;
        inputUpdateValue = nullptr;
        goUpdate = nullptr;

        updateMenu.frame = updateMenu.mainframe->addHBoxLayout();
        inputUpdateIndex = new gui::TextBox(80);
        inputUpdateIndex->setMaxLength(1);
        inputUpdateIndex->setPlaceholder("Index");
        updateMenu.frame->add(inputUpdateIndex);

        inputUpdateValue = new gui::TextBox(80);
        inputUpdateValue->setMaxLength(2);
        inputUpdateValue->setPlaceholder("Value");
        updateMenu.frame->add(inputUpdateValue);

        goUpdate = updateMenu.frame->addButton("GO", [this]{
            if(!inputUpdateIndex->getText().toAnsiString().empty() && !inputUpdateValue->getText().toAnsiString().empty()){
                try{
                    linkedList.updateNode(std::stoi(inputUpdateIndex->getText().toAnsiString()), std::stoi(inputUpdateValue->getText().toAnsiString()));
                }catch(std::invalid_argument){
                    //do nothing
                }
            }
        });
    });
    insertMenu.mainButton->setCallback([this]{
        insertMenu.deleteFrame();
        //init
        insertMenu.frame = nullptr;
        insertHead = nullptr;
        insertTail = nullptr;
        insertArbitrary = nullptr;
        inputInsertIndex = nullptr;
        inputInsertValue = nullptr;
        insertFrame = nullptr;

        insertMenu.frame = insertMenu.mainframe->addHBoxLayout();

        insertHeadFrame = insertMenu.frame->addVBoxLayout();
        insertTailFrame = insertMenu.frame->addVBoxLayout();
        insertArbitraryFrame = insertMenu.frame->addVBoxLayout();

        insertHead = new gui::SpriteButton(buttonBG, "Head");
        insertTail = new gui::SpriteButton(buttonBG, "Tail");
        insertArbitrary = new gui::SpriteButton(buttonBG, "Arbitrary");

        insertHeadFrame->add(insertHead);
        insertTailFrame->add(insertTail);
        insertArbitraryFrame->add(insertArbitrary);

        insertHead->setCallback([this]{
            if(insertHeadFrame->m_last == insertFrame)
                insertHeadFrame->removeLast();
            if(insertTailFrame->m_last == insertFrame)
                insertTailFrame->removeLast();
            if(insertArbitraryFrame->m_last == insertFrame)
                insertArbitraryFrame->removeLast();
            insertFrame = nullptr;
            inputInsertValue = nullptr;
            inputInsertIndex = nullptr;

            insertFrame = insertHeadFrame->addHBoxLayout();
            inputInsertValue = new gui::TextBox(100);
            inputInsertValue->setMaxLength(2);
            inputInsertValue->setPlaceholder("Value");
            insertFrame->add(inputInsertValue);
            goInsert = insertFrame->addButton("GO", [this]{
                if(!inputInsertValue->getText().toAnsiString().empty())
                    try{
                        linkedList.insertToHead(std::stoi(inputInsertValue->getText().toAnsiString()));
                    }catch(std::invalid_argument){
                        //do nothing
                    }
            });
            insertHeadFrame->recomputeGeometry();
            insertTailFrame->recomputeGeometry();
            insertArbitraryFrame->recomputeGeometry();
        });

        insertTail->setCallback([this]{
            if(insertHeadFrame->m_last == insertFrame)
                insertHeadFrame->removeLast();
            if(insertTailFrame->m_last == insertFrame)
                insertTailFrame->removeLast();
            if(insertArbitraryFrame->m_last == insertFrame)
                insertArbitraryFrame->removeLast();
            insertFrame = nullptr;
            inputInsertValue = nullptr;
            inputInsertIndex = nullptr;

            insertFrame = insertTailFrame->addHBoxLayout();
            inputInsertValue = new gui::TextBox(100);
            inputInsertValue->setMaxLength(2);
            inputInsertValue->setPlaceholder("Value");
            insertFrame->add(inputInsertValue);
            goInsert = insertFrame->addButton("GO", [this]{
                if(!inputInsertValue->getText().toAnsiString().empty()){
                    try{
                        linkedList.insertToTail(std::stoi(inputInsertValue->getText().toAnsiString()));
                    }catch(std::invalid_argument){
                        //do nothing
                    }
                }
            });
            insertHeadFrame->recomputeGeometry();
            insertTailFrame->recomputeGeometry();
            insertArbitraryFrame->recomputeGeometry();
        });

        insertArbitrary->setCallback([this]{
            if(insertHeadFrame->m_last == insertFrame)
                insertHeadFrame->removeLast();
            if(insertTailFrame->m_last == insertFrame)
                insertTailFrame->removeLast();
            if(insertArbitraryFrame->m_last == insertFrame)
                insertArbitraryFrame->removeLast();
            insertFrame = nullptr;
            inputInsertValue = nullptr;
            inputInsertIndex = nullptr;

            insertFrame = insertArbitraryFrame->addHBoxLayout();
            inputInsertValue = new gui::TextBox(100);
            inputInsertValue->setMaxLength(2);
            inputInsertValue->setPlaceholder("Value");
            insertFrame->add(inputInsertValue);

            inputInsertIndex = new gui::TextBox(100);
            inputInsertIndex->setMaxLength(2);
            inputInsertIndex->setPlaceholder("Index");
            insertFrame->add(inputInsertIndex);

            goInsert = insertFrame->addButton("GO", [this]{
                if(!inputInsertValue->getText().toAnsiString().empty() && !inputInsertIndex->getText().toAnsiString().empty()) {
                    try {
                        linkedList.insertArbitrary(std::stoi(inputInsertValue->getText().toAnsiString()),
                                                   std::stoi(inputInsertIndex->getText().toAnsiString()));
                    } catch (std::invalid_argument) {
                        //do nothing
                    }
                }
            });
            insertHeadFrame->recomputeGeometry();
            insertTailFrame->recomputeGeometry();
            insertArbitraryFrame->recomputeGeometry();
        });
    });
    deleteMenu.mainButton->setCallback([this]{
        deleteMenu.deleteFrame();
        //init
        deleteMenu.frame = nullptr;
        deleteHead = nullptr;
        deleteTail = nullptr;
        deleteArbitrary = nullptr;
        inputDeleteIndex = nullptr;
        deleteFrame = nullptr;

        deleteMenu.frame = deleteMenu.mainframe->addHBoxLayout();

        deleteHeadFrame = deleteMenu.frame->addVBoxLayout();
        deleteTailFrame = deleteMenu.frame->addVBoxLayout();
        deleteArbitraryFrame = deleteMenu.frame->addVBoxLayout();

        deleteHead = new gui::SpriteButton(buttonBG, "Head");
        deleteTail = new gui::SpriteButton(buttonBG, "Tail");
        deleteArbitrary = new gui::SpriteButton(buttonBG, "Arbitrary");

        deleteHeadFrame->add(deleteHead);
        deleteTailFrame->add(deleteTail);
        deleteArbitraryFrame->add(deleteArbitrary);

        deleteHead->setCallback([this]{
            linkedList.deleteHead();
        });

        deleteTail->setCallback([this]{
            linkedList.deleteTail();
        });

        deleteArbitrary->setCallback([this]{
            if(deleteHeadFrame->m_last == deleteFrame)
                deleteHeadFrame->removeLast();
            if(deleteTailFrame->m_last == deleteFrame)
                deleteTailFrame->removeLast();
            if(deleteArbitraryFrame->m_last == deleteFrame)
                deleteArbitraryFrame->removeLast();
            deleteFrame = nullptr;
            inputDeleteIndex = nullptr;

            deleteFrame = deleteArbitraryFrame->addHBoxLayout();
            inputDeleteIndex = new gui::TextBox(100);
            inputDeleteIndex->setMaxLength(1);
            inputDeleteIndex->setPlaceholder("Index");
            deleteFrame->add(inputDeleteIndex);

            goDelete = deleteFrame->addButton("GO", [this]{
                if(!inputDeleteIndex->getText().toAnsiString().empty()){
                    try{
                        linkedList.deleteArbitrary(std::stoi(inputDeleteIndex->getText().toAnsiString()));
                    }catch(std::invalid_argument){
                        //do nothing
                    }
                }
            });
            deleteHeadFrame->recomputeGeometry();
            deleteTailFrame->recomputeGeometry();
            deleteArbitraryFrame->recomputeGeometry();
        });
    });

    mediaBar.m_forwardButton->setCallback([this]{
        linkedList.fastForward();
    });
    mediaBar.m_backwardButton->setCallback([this]{
        linkedList.rewind();
    });
    mediaBar.m_playButton->setCallback([this]{
        if(linkedList.isPausing)
            linkedList.resume();
        else
            linkedList.pause();
    });

    changeWindow = new gui::OptionsBox<windowType>();
    changeWindow->addItem("Singly Linked List",singlyLinkedListWindow);
    changeWindow->addItem("Doubly Linked List",doublyLinkedListWindow);
    changeWindow->addItem("Circular Linked List",circularLinkedListWindow);
    changeWindow->addItem("Stack",stackWindow);
    changeWindow->addItem("Queue",queueWindow);

    changeWindow->selectItem(0);
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

displayLinkedList::~displayLinkedList() {

}

windowType displayLinkedList::mainloop(sf::RenderWindow &window) {
    nextWindow = singlyLinkedListWindow;
    while (window.isOpen() && nextWindow == singlyLinkedListWindow)
    {
        sf::Event event;


        while (window.pollEvent(event))
        {
            // Send events to menu
            menu.onEvent(event);
            linkedList.onEvent(event);
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
        if(!searchMenu.mainframe->isFocused()){
            searchMenu.deleteFrame();
            searchMenu.mainframe->recomputeGeometry();
//            menu.recomputeGeometry();
        }
        if(!updateMenu.mainframe->isFocused()){
            updateMenu.deleteFrame();
            updateMenu.mainframe->recomputeGeometry();
        }
        if(!insertMenu.mainframe->isFocused()){
            insertMenu.deleteFrame();
            insertMenu.mainframe->recomputeGeometry();
//            menu.recomputeGeometry();
        }
        if(!deleteMenu.mainframe->isFocused()){
            deleteMenu.deleteFrame();
            deleteMenu.mainframe->recomputeGeometry();
//            menu.recomputeGeometry();
        }

        mediaBar.setPauseState(linkedList.isPausing);

        mediaBar.m_backwardButton->setPosition(sf::Vector2f {860,1000} - menu.getPosition());
        mediaBar.m_playButton->setPosition(sf::Vector2f {960,1000} - menu.getPosition());
        mediaBar.m_forwardButton->setPosition(sf::Vector2f {1060,1000} - menu.getPosition());

        changeWindow->setPosition(sf::Vector2f {10,10} - menu.getPosition());
        backToMenu->setPosition(sf::Vector2f {1750,10} - menu.getPosition());

        window.clear(gui::Theme::windowBgColor);


        bg.draw(window);

        mediaBar.draw(window);
        linkedList.draw(window);
        window.draw(menu);
        // Update the window
        window.display();
    }
    return nextWindow;
}
