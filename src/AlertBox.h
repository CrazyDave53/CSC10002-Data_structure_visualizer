#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_ALERTBOX_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_ALERTBOX_H

#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>

class AlertBox {
public:
    AlertBox();
    AlertBox(std::string message);
    void setMessage(std::string message);
    void setEnabled(bool enabled);
    void draw(sf::RenderWindow& window);
    bool isCloseButtonPressed(sf::Event event);

private:
    std::string m_message;
    bool m_enabled;
    sf::Font m_font;
    sf::RectangleShape m_background;
    sf::Text m_text;
    sf::RectangleShape m_closeButton;
    sf::Text m_closeText;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_ALERTBOX_H
