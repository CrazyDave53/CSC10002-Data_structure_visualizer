#include "mediaBar.h"
#include "utilities.h"

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

    m_speedSlider = new gui::Slider(300, gui::Horizontal);
    m_speedSlider->setStep(5);
    m_speedSlider->setValue(50);

    m_speedText = new sf::Text("SPEED: 100%", gui::Theme::getFont(), 20);

    menu.add(m_backwardButton);
    menu.add(m_playButton);
    menu.add(m_forwardButton);
    menu.add(m_speedSlider);

    m_speedSlider->setCallback([this](){
        utility::setMultiplier(0.5 + (m_speedSlider->getValue() * 0.01f));
        m_speedText->setString("SPEED: " + std::to_string(m_speedSlider->getValue() + 50) + "%");
    });

    m_background.setSize(sf::Vector2f(1920, 100));
    m_background.setFillColor(sf::Color(251, 113, 146, 100));
    m_background.setPosition(0, 990);
}

mediaBar::~mediaBar() {
    m_playButton = nullptr;
    m_forwardButton = nullptr;
    m_backwardButton = nullptr;

    m_speedSlider = nullptr;

    delete m_speedText;
    m_speedText = nullptr;
}

void mediaBar::draw(sf::RenderWindow& window) {
//    m_mediaBar->draw(window, sf::RenderStates::Default);
    m_speedText->setPosition(sf::Vector2f {440,1006});
    window.draw(m_background);
    window.draw(*m_speedText);
}

void mediaBar::setPauseState(bool state) {
    if(state){
        m_playButton->setTexture(m_pauseButtonTexture);
    }
    else{
        m_playButton->setTexture(m_playButtonTexture);
    }
}
