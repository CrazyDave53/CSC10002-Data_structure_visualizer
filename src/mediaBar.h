#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_MEDIABAR_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_MEDIABAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Gui/Gui.hpp"

class mediaBar{
public:
    mediaBar(gui::Menu &menu);
    ~mediaBar();
    void draw(sf::RenderWindow& window);
    void setPauseState(bool state);
    gui::SpriteButton* m_playButton;
    gui::SpriteButton* m_forwardButton;
    gui::SpriteButton* m_backwardButton;

    gui::Slider* m_speedSlider;
    sf::Text* m_speedText;

    gui::HBoxLayout* m_mediaBar;
private:

    sf::RectangleShape m_background;

    sf::Texture m_playButtonTexture;
    sf::Texture m_pauseButtonTexture;
    sf::Texture m_forwardButtonTexture;
    sf::Texture m_backwardButtonTexture;
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_MEDIABAR_H
