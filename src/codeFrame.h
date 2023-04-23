#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_CODEFRAME_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_CODEFRAME_H

#include <SFML/Graphics.hpp>

class CodeFrame
{
public:
    CodeFrame();
    void setText(const std::vector<std::string>& lines);
    void setHighlight(int lineIndex);
    void deHighlightAll();
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    void setPosition(float x, float y);
    sf::Vector2f getSize();

private:
    void update();
    std::vector<sf::Text> m_textLines;
    std::vector<bool> m_lineIsHighlighted;
    sf::Font m_font;
    sf::RectangleShape m_background;
    sf::RectangleShape m_lineNumbersBackground;
    sf::RectangleShape m_highlightedLineBackground;
    std::vector<sf::Text> m_lineNumbers;
    sf::Vector2f m_position;
    float linePadding;
    float maxWidth;
    float totalHeight;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_CODEFRAME_H
