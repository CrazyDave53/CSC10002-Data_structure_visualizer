#include "codeFrame.h"

CodeFrame::CodeFrame() :
m_position(0.f, 0.f),
m_font(),
m_background(),
m_lineNumbersBackground(),
m_highlightedLineBackground(),
m_textLines(),
m_lineNumbers(),
linePadding(10.f),
maxWidth(),
totalHeight(),
m_lineIsHighlighted()


{
    if (!m_font.loadFromFile("./fonts/ARLRDBD.TTF")) // Replace with your desired font file
    {
        // Error handling
    }
    m_background.setFillColor(sf::Color(0, 0, 0, 75)); // Replace with your desired background color and opacity
    m_lineNumbersBackground.setFillColor(sf::Color(200, 200, 200, 75)); // Replace with your desired line number background color and opacity
    m_lineNumbersBackground.setSize(sf::Vector2f(40.f, 0.f)); // Set initial size of line number background

}

void CodeFrame::setText(const std::vector<std::string>& lines)
{
    m_textLines.clear();
    m_lineNumbers.clear();
    for (const auto& line : lines)
    {
        sf::Text text(line, m_font);
        m_textLines.push_back(text);

        sf::Text lineNumberText(std::to_string(m_lineNumbers.size() + 1), m_font);
        m_lineNumbers.push_back(lineNumberText);
    }
    deHighlightAll();
    update();
}

void CodeFrame::setHighlight(int lineIndex)
{
    m_lineIsHighlighted[lineIndex] = true;
}

void CodeFrame::draw(sf::RenderWindow& window)
{
    update();
    for (int i = 0; i < m_textLines.size(); i++)
    {
        auto& text = m_textLines[i];
        auto& lineNumber = m_lineNumbers[i];
        text.setPosition(m_lineNumbersBackground.getSize().x + 5.f + m_position.x, i * (m_textLines[0].getLocalBounds().height + linePadding) + 5.f + m_position.y); // Add padding to text position
        lineNumber.setPosition(5.f + m_position.x, i * (m_textLines[0].getLocalBounds().height + linePadding) + 5.f + m_position.y); // Add padding to line number position
        if (m_lineIsHighlighted[i]){
            m_highlightedLineBackground.setSize(sf::Vector2f(maxWidth, m_textLines[0].getLocalBounds().height + 13.f));
            m_highlightedLineBackground.setFillColor(sf::Color(251, 113, 146, 150)); // Replace with your desired highlighted line background color and opacity
            m_highlightedLineBackground.setPosition(m_lineNumbersBackground.getSize().x + 5.f + m_position.x, i * (m_textLines[0].getLocalBounds().height + linePadding) + 5.f + m_position.y);
            window.draw(m_highlightedLineBackground);
        }
        else
        {
            text.setStyle(sf::Text::Style::Regular);
        }
        window.draw(text);
        window.draw(lineNumber);
    }
    window.draw(m_background);
    window.draw(m_lineNumbersBackground);
}

void CodeFrame::setPosition(float x, float y)
{
    m_position = sf::Vector2f(x, y);
}

void CodeFrame::update() {
    // Calculate size of background rectangle based on text size
    maxWidth = 0;
    float totalHeight = 0;
    for (const auto& text : m_textLines)
    {
        auto textWidth = text.getLocalBounds().width;
        if (textWidth > maxWidth)
        {
            maxWidth = textWidth;
        }
        totalHeight += m_textLines[0].getLocalBounds().height + linePadding;
    }
    m_background.setSize(sf::Vector2f(maxWidth + 10.f + m_lineNumbersBackground.getSize().x, totalHeight + 13.f)); // Add padding to background size
    m_background.setPosition(m_position);

    m_lineNumbersBackground.setSize(sf::Vector2f(m_lineNumbersBackground.getSize().x, totalHeight + 13.f));
    m_lineNumbersBackground.setPosition(m_position);
}

sf::Vector2f CodeFrame::getPosition()
{
    return m_position;
}

sf::Vector2f CodeFrame::getSize() {
    return {m_background.getSize().x, m_background.getSize().y};
}

void CodeFrame::deHighlightAll() {
    m_lineIsHighlighted.clear();
    m_lineIsHighlighted.assign(m_textLines.size(), false);
}

