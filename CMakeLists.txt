cmake_minimum_required(VERSION 3.24)
project(CSC10002_Data_structure_visualizer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(CSC10002_Data_structure_visualizer
        src/main.cpp src/render.cpp src/render.h src/menu.h src/menu.cpp src/Button.cpp src/Button.h src/selectingMenu.cpp src/selectingMenu.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(TGUI_STATIC_LIBRARIES TRUE)

set(SFML_DIR C:/SFML/lib/cmake/SFML)
set(TGUI_DIR C:/TGUI-1.0/lib/cmake/TGUI)

find_package(TGUI)

find_package(SFML COMPONENTS window graphics audio REQUIRED)

target_link_libraries(CSC10002_Data_structure_visualizer sfml-graphics sfml-audio sfml-window TGUI::TGUI)
