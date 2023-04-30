#include "AlertBox.h"

#include "alertbox.h"

AlertBox::AlertBox() :
        m_message(),
        m_enabled(),
        m_font(),
        m_background(),
        m_text(),
        m_closeButton(),
        m_closeText()
{
    if (!m_font.loadFromFile("./fonts/ARLRDBD.TTF")) {

    }

    m_background.setSize(sf::Vector2f(400.f, 200.f));
    m_background.setFillColor(sf::Color(194, 85, 110, 255));
    m_background.setOutlineThickness(2.f);
    m_background.setOutlineColor(sf::Color::Black);
    m_background.setPosition((1920.f - m_background.getSize().x) / 2.f,
                             (1080.f - m_background.getSize().y) / 2.f);

    m_text.setString("");
    m_text.setFont(m_font);
    m_text.setCharacterSize(30);
    m_text.setFillColor(sf::Color::White);
    m_text.setPosition(m_background.getPosition().x + 50.f, m_background.getPosition().y + 50.f);

    m_closeButton.setSize(sf::Vector2f(30.f, 30.f));
    m_closeButton.setFillColor(sf::Color::Red);
    m_closeButton.setPosition(m_background.getPosition().x + m_background.getSize().x - m_closeButton.getSize().x - 10.f,
                              m_background.getPosition().y + 10.f);

    m_closeText.setString("X");
    m_closeText.setFont(m_font);
    m_closeText.setCharacterSize(20);
    m_closeText.setFillColor(sf::Color::White);
    m_closeText.setPosition(m_closeButton.getPosition().x + 7.f, m_closeButton.getPosition().y + 1.f);

//    m_background.setOutlineThickness(5.f);
//    m_background.setOutlineColor(sf::Color::Black);
//    m_closeButton.setOutlineThickness(2.f);
//    m_closeButton.setOutlineColor(sf::Color::Black);

    m_enabled = false;
}

AlertBox::AlertBox(std::string message)
        : AlertBox()
{
    setMessage(message);
}

void AlertBox::setMessage(std::string message) {
    m_message = message;
    m_text.setString(m_message);
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin(textBounds.left + textBounds.width / 2.f,
                     textBounds.top + textBounds.height / 2.f);
    m_background.setSize(sf::Vector2f(textBounds.width + 100.f, textBounds.height + 50.f));
    m_background.setPosition((1920.f - m_background.getSize().x) / 2.f,
                             (1080.f - m_background.getSize().y) / 2.f);
    m_text.setPosition(m_background.getPosition().x + m_background.getSize().x / 2.f,
                       m_background.getPosition().y + m_background.getSize().y / 2.f);
    m_closeButton.setPosition(m_background.getPosition().x + m_background.getSize().x - m_closeButton.getSize().x - 10.f,
                              m_background.getPosition().y + 10.f);
    m_closeText.setPosition(m_closeButton.getPosition().x + 7.f, m_closeButton.getPosition().y + 1.f);
}

void AlertBox::setEnabled(bool enabled) {
    m_enabled = enabled;
}

void AlertBox::draw(sf::RenderWindow& window) {
    if (m_enabled) {
        window.draw(m_background);
        window.draw(m_text);
        window.draw(m_closeButton);
        window.draw(m_closeText);
    }
}

bool AlertBox::isCloseButtonPressed(sf::Event event) {
    if (m_enabled) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (m_closeButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    m_enabled = false;
                    return true;
                }
            }
        }
    }
    return false;
}
