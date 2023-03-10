#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_BUTTON_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button();
    Button(sf::Vector2f centre, sf::Vector2f size, std::string text, sf::Font font, sf::Color backgroundColor, sf::Color textColor, int textSize, float cornerRadius);
    void draw(sf::RenderTarget& target, sf::RenderStates states);
//bool isClicked(const sf::RenderWindow& window);
private:
    sf::RectangleShape ButtonShape;
    sf::Text ButtonText;
    sf::Vector2f pos;
    sf::Vector2f centre;
    float ButtonCornerRadius;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_BUTTON_H
