#include "displayLinkedList.h"
#include <iostream>
#include <string>
displayLinkedList::displayLinkedList(sf::RenderWindow &window):
    menu(window),
    nextWindow(singlyLinkedListWindow),
    createMenu(menu, "Create"),
    searchMenu(menu, "Search"),
    insertMenu(menu, "Insert"),
    deleteMenu(menu, "Delete"),
    createRandom(),
    createRandomFrame(),
    createRandomSizeFrame(),
    inputSearchValue(),
    goSearch(),
    buttonBG(),
    linkedList(),

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

    bg()
{
    menu.setPosition(100,600);
    buttonBG.loadFromFile("./assets/button/newbutton.png");
    createMenu.mainButton->setCallback([this]{
        createMenu.deleteFrame();
        //init null
        createRandomFrame = nullptr;
        createRandomSizeFrame = nullptr;
        goCreateRandom = nullptr;
        inputSizeCreateRandom = nullptr;

        createMenu.frame = createMenu.mainframe->addHBoxLayout();

        createRandomFrame = createMenu.frame->addVBoxLayout();
        createRandom = new gui::SpriteButton(buttonBG,"Random");
        createRandomFrame->add(createRandom);
        createRandom->setCallback([this]{
            if(createRandomSizeFrame != nullptr){
                createRandomFrame->removeLast();//remove createRandomSizeFrame
                inputSizeCreateRandom = nullptr;
                goCreateRandom = nullptr;
            }
            createRandomSizeFrame = createRandomFrame->addHBoxLayout();
            inputSizeCreateRandom = new gui::TextBox(100);
            inputSizeCreateRandom->setMaxLength(1);
            inputSizeCreateRandom->setPlaceholder("Input size");
            createRandomSizeFrame->add(inputSizeCreateRandom);
            goCreateRandom = createRandomSizeFrame->addButton("GO", [this]{
                if(inputSizeCreateRandom->getText().toAnsiString() != "")
                    linkedList.createRandom(std::stoi(inputSizeCreateRandom->getText().toAnsiString()));
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
            if(inputSearchValue->getText().toAnsiString() != ""){
                linkedList.search(std::stoi(inputSearchValue->getText().toAnsiString()));
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
                if(inputInsertValue->getText().toAnsiString() != "")
                    linkedList.insertToHead(std::stoi(inputInsertValue->getText().toAnsiString()));
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
                if(inputInsertValue->getText().toAnsiString() != "")
                    linkedList.insertToTail(std::stoi(inputInsertValue->getText().toAnsiString()));
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
                if(inputInsertValue->getText().toAnsiString() != "" && inputInsertIndex->getText().toAnsiString() != "")
                    linkedList.insertArbitrary(std::stoi(inputInsertValue->getText().toAnsiString()), std::stoi(inputInsertIndex->getText().toAnsiString()));
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

        });

        deleteTail->setCallback([this]{

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
            inputDeleteIndex->setMaxLength(2);
            inputDeleteIndex->setPlaceholder("Index");
            deleteFrame->add(inputDeleteIndex);

            goDelete = deleteFrame->addButton("GO", [this]{
//                if(inputDeleteIndex->getText().toAnsiString() != "")
//                    linkedList.deleteArbitrary(std::stoi(inputDeleteIndex->getText().toAnsiString()));
            });
            deleteHeadFrame->recomputeGeometry();
            deleteTailFrame->recomputeGeometry();
            deleteArbitraryFrame->recomputeGeometry();
        });
    });
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
            if (event.type == sf::Event::Closed)
                window.close();
        }
//        std::cout << createMenu.frame << "\n";
        // Clear screen
        if(!createMenu.mainframe->isFocused()){
            createMenu.deleteFrame();
            createMenu.mainframe->recomputeGeometry();
            menu.recomputeGeometry();
        }
        if(!searchMenu.mainframe->isFocused()){
            searchMenu.deleteFrame();
            searchMenu.mainframe->recomputeGeometry();
            menu.recomputeGeometry();
        }
        if(!insertMenu.mainframe->isFocused()){
            insertMenu.deleteFrame();
            insertMenu.mainframe->recomputeGeometry();
            menu.recomputeGeometry();
        }
        window.clear(gui::Theme::windowBgColor);

        bg.draw(window);
        linkedList.draw(window);
        window.draw(menu);
        // Update the window
        window.display();
    }
    return nextWindow;
}
