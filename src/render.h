#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_RENDER_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_RENDER_H

#define mainMenu 0
#define selecting 1


#include <string>
#include <SFML/Graphics.hpp>

class Application{
    private:
        int windowType = 0;
        sf::RenderWindow window;
        sf::Font font;


    public:
        void changeWindowtype(int type);
        void renderWindow();
        void initWindow();
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_RENDER_H