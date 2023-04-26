cmake_minimum_required(VERSION 3.24)
project(CSC10002-Data_structure_visualizer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(CSC10002-Data_structure_visualizer
        src/main.cpp src/render.cpp src/render.h src/menu.h src/menu.cpp src/Button.cpp src/Button.h src/selectingMenu.cpp src/selectingMenu.h Gui/Button.cpp Gui/SpriteButton.cpp Gui/CheckBox.cpp Gui/Slider.cpp Gui/Label.cpp Gui/Layouts/Layout.cpp Gui/Layouts/FormLayout.cpp Gui/Menu.cpp Gui/Layouts/VBoxLayout.cpp Gui/Layouts/HBoxLayout.cpp Gui/TextBox.cpp Gui/Image.cpp Gui/ProgressBar.cpp Gui/Theme.cpp Gui/Widget.cpp Gui/Utils/Arrow.cpp Gui/Utils/Box.cpp Gui/Utils/Cross.cpp src/mainMenu.cpp src/mainMenu.h src/mainMenu.cpp src/mainMenu.h src/mainMenu.h src/mainMenu.cpp src/mainMenu.h src/windowsList.h src/linkedList.cpp src/linkedList.h src/displayLinkedList.cpp src/displayLinkedList.h src/popUpMenu.cpp src/popUpMenu.h src/movable.cpp src/movable.h src/movable.h src/node.cpp src/node.h src/node.h src/arrow.cpp src/arrow.h src/numberSprite.cpp src/numberSprite.h src/transition.cpp src/transition.h src/background.cpp src/background.h src/codeFrame.cpp src/codeFrame.h src/mediaBar.cpp src/mediaBar.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(TGUI_STATIC_LIBRARIES TRUE)

set(SFML_DIR C:/SFML/lib/cmake/SFML)
set(TGUI_DIR C:/TGUI-1.0/lib/cmake/TGUI)

find_package(TGUI)

find_package(SFML COMPONENTS window graphics audio REQUIRED)

target_link_libraries(CSC10002-Data_structure_visualizer sfml-graphics sfml-audio sfml-window TGUI::TGUI)
