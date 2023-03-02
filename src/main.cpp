#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(400, 300), "Menu");
    Font font;
    font.loadFromFile("ARLRDBD.TTF"); // Replace with the path to your font file
    Text title("Menu", font, 50);
    title.setPosition(100, 50);
    Text option1("Option 1", font, 30);
    option1.setPosition(100, 120);
    Text option2("Option 2", font, 30);
    option2.setPosition(100, 160);
    Text option3("Option 3", font, 30);
    option3.setPosition(100, 200);
    Text exit("Exit", font, 30);
    exit.setPosition(100, 240);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (option1.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    cout << "You selected Option 1" << endl;
                }
                if (option2.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    cout << "You selected Option 2" << endl;
                }
                if (option3.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    cout << "You selected Option 3" << endl;
                }
                if (exit.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    cout << "Exiting program..." << endl;
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(title);
        window.draw(option1);
        window.draw(option2);
        window.draw(option3);
        window.draw(exit);
        window.display();
    }

    return 0;
}