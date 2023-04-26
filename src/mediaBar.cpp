#include "mediaBar.h"

mediaBar::mediaBar(gui::Menu &menu) :
    m_playButtonTexture(),
    m_pauseButtonTexture(),
    m_forwardButtonTexture(),
    m_backwardButtonTexture(),
    m_playButton(),
    m_forwardButton(),
    m_backwardButton(),
    m_background()
{
    m_playButtonTexture.loadFromFile("assets/textures/play.png");
    m_pauseButtonTexture.loadFromFile("assets/textures/pause.png");
    m_forwardButtonTexture.loadFromFile("assets/textures/fastForward.png");
    m_backwardButtonTexture.loadFromFile("assets/textures/rewind.png");

    m_playButton = new gui::SpriteButton(m_playButtonTexture,"");
    m_forwardButton = new gui::SpriteButton(m_forwardButtonTexture, "");
    m_backwardButton = new gui::SpriteButton(m_backwardButtonTexture, "");

//    m_mediaBar = menu.addHBoxLayout();
//    m_mediaBar->add(m_backwardButton);
//    m_mediaBar->add(m_playButton);
//    m_mediaBar->add(m_forwardButton);

    menu.add(m_backwardButton);
    menu.add(m_playButton);
    menu.add(m_forwardButton);

    m_background.setSize(sf::Vector2f(1920, 100));
    m_background.setFillColor(sf::Color(251, 113, 146, 100));
    m_background.setPosition(0, 990);
}

mediaBar::~mediaBar() {
    delete m_playButton;
    delete m_forwardButton;
    delete m_backwardButton;
}

void mediaBar::draw(sf::RenderWindow& window) {
//    m_mediaBar->draw(window, sf::RenderStates::Default);
    window.draw(m_background);
}

void mediaBar::setPauseState(bool state) {
    if(state){
        m_playButton->setTexture(m_pauseButtonTexture);
    }
    else{
        m_playButton->setTexture(m_playButtonTexture);
    }
}
