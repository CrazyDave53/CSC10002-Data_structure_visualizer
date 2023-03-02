cmake_minimum_required(VERSION 3.24)
project(CSC10002_Data_structure_visualizer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(CSC10002_Data_structure_visualizer
        src/main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS window graphics audio REQUIRED)

target_link_libraries(CSC10002_Data_structure_visualizer sfml-graphics sfml-audio sfml-window)
