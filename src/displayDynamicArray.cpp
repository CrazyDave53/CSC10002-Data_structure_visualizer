#include "displayDynamicArray.h"
#include <iostream>
#include <string>
displayDynamicArray::displayDynamicArray(sf::RenderWindow &window):
        menu(window),
        nextWindow(dynamicArrayWindow),
        mediaBar(menu),
        createMenu(menu, "Create"),
        searchMenu(menu, "Search"),
        updateMenu(menu, "Update"),
        insertMenu(menu, "Insert"),
        deleteMenu(menu, "Delete"),
        allocateMenu(menu, "Allocate"),

        dynamicArray(),
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
                        dynamicArray.createRandom(std::stoi(inputCreate->getText().toAnsiString()));
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
                dynamicArray.createFromFile();
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
                    dynamicArray.createUserInput(inputCreate->getText().toAnsiString());
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
                    dynamicArray.search(std::stoi(inputSearchValue->getText().toAnsiString()));
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
                    dynamicArray.updateElement(std::stoi(inputUpdateIndex->getText().toAnsiString()), std::stoi(inputUpdateValue->getText().toAnsiString()));
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
                        dynamicArray.insertToHead(std::stoi(inputInsertValue->getText().toAnsiString()));
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
                        dynamicArray.insertToTail(std::stoi(inputInsertValue->getText().toAnsiString()));
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
                        dynamicArray.insert(std::stoi(inputInsertValue->getText().toAnsiString()),
                                                   std::stoi(inputInsertIndex->getText().toAnsiString()));
//                            dynamicArray.transferToArray();
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
            dynamicArray.deleteHead();
        });

        deleteTail->setCallback([this]{
            dynamicArray.deleteTail();
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
                        dynamicArray.deleteElement(std::stoi(inputDeleteIndex->getText().toAnsiString()));
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

    allocateMenu.mainButton->setCallback([this]{
        allocateMenu.deleteFrame();
        //init ptr
        allocateMenu.frame = nullptr;

        allocateMenu.frame = allocateMenu.mainframe->addHBoxLayout();
        inputAllocateSize = new gui::TextBox(110);
        inputAllocateSize->setMaxLength(2);
        inputAllocateSize->setPlaceholder("Size");
        allocateMenu.frame->add(inputAllocateSize);;

        goAllocate = allocateMenu.frame->addButton("GO",[this]{
            if(!inputAllocateSize->getText().toAnsiString().empty()){
                try{
                    dynamicArray.allocate(std::stoi(inputAllocateSize->getText().toAnsiString()));
                }catch(std::invalid_argument){
                    //do nothing
                }
            }
        });
    });

    mediaBar.m_forwardButton->setCallback([this]{
        dynamicArray.fastForward();
    });
    mediaBar.m_backwardButton->setCallback([this]{
        dynamicArray.rewind();
    });
    mediaBar.m_playButton->setCallback([this]{
        if(dynamicArray.isPausing)
            dynamicArray.resume();
        else
            dynamicArray.pause();
    });

    changeWindow = new gui::OptionsBox<windowType>();
    changeWindow->addItem("Singly Linked List",singlyLinkedListWindow);
    changeWindow->addItem("Doubly Linked List",doublyLinkedListWindow);
    changeWindow->addItem("Circular Linked List",circularLinkedListWindow);
    changeWindow->addItem("Stack",stackWindow);
    changeWindow->addItem("Queue",queueWindow);
    changeWindow->addItem("Static Array",staticArrayWindow);
    changeWindow->addItem("Dynamic Array",dynamicArrayWindow);

    changeWindow->selectItem(6);
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

displayDynamicArray::~displayDynamicArray() {

}

windowType displayDynamicArray::mainloop(sf::RenderWindow &window) {
    nextWindow = dynamicArrayWindow;
    while (window.isOpen() && nextWindow == dynamicArrayWindow)
    {
        sf::Event event;


        while (window.pollEvent(event))
        {
            // Send events to menu
            menu.onEvent(event);
            dynamicArray.onEvent(event);
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

        mediaBar.setPauseState(dynamicArray.isPausing);

        mediaBar.m_backwardButton->setPosition(sf::Vector2f {860,1000} - menu.getPosition());
        mediaBar.m_playButton->setPosition(sf::Vector2f {960,1000} - menu.getPosition());
        mediaBar.m_forwardButton->setPosition(sf::Vector2f {1060,1000} - menu.getPosition());

        changeWindow->setPosition(sf::Vector2f {10,10} - menu.getPosition());
        backToMenu->setPosition(sf::Vector2f {1750,10} - menu.getPosition());

        window.clear(gui::Theme::windowBgColor);


        bg.draw(window);

        mediaBar.draw(window);
        dynamicArray.draw(window);
        window.draw(menu);
        // Update the window
        window.display();
    }
    return nextWindow;
}
