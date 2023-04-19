#include "arrow.h"
#include <cmath>

Arrow::Arrow(sf::Vector2f start, sf::Vector2f end)
        : m_thickness(5.f), m_triangleSize(15.f), m_start(start), m_end(end)
{
    // Calculate length and angle of arrow line
    sf::Vector2f diff = end - start;
    float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    float angle = std::atan2(diff.y, diff.x) * 180.f / M_PI;

    // Create rectangle
    m_rect.setSize(sf::Vector2f(length, m_thickness));
    m_rect.setOrigin(0.f, m_thickness / 2.f);
    m_rect.setPosition(start);
    m_rect.setRotation(angle);
        m_rect.setFillColor(sf::Color::White);

    // Create triangle
    m_triangle.setPointCount(3);
    m_triangle.setPoint(0, sf::Vector2f(0.f, 0.f));
    m_triangle.setPoint(1, sf::Vector2f(-m_triangleSize, m_triangleSize / 2.f));
    m_triangle.setPoint(2, sf::Vector2f(-m_triangleSize, -m_triangleSize / 2.f));
    m_triangle.setOrigin(0, 0.f);
    m_triangle.setPosition(end);
    m_triangle.setRotation(angle);
    m_triangle.setFillColor(sf::Color::White);
}

void Arrow::setThickness(float thickness)
{
    m_thickness = thickness;
    m_rect.setSize(sf::Vector2f(m_rect.getSize().x, thickness));
    m_rect.setOrigin(0.f, thickness / 2.f);
}

void Arrow::setTriangleSize(float size)
{
    m_triangleSize = size;
    m_triangle.setPoint(1, sf::Vector2f(-size, size / 2.f));
    m_triangle.setPoint(2, sf::Vector2f(-size, -size / 2.f));
}

void Arrow::setStart(sf::Vector2f start){
    m_start = start;
    update();
}

void Arrow::setEnd(sf::Vector2f end) {
    m_end = end;
    update();
}


void Arrow::moveEnd(sf::Vector2f end) {
    pos = m_start;
    setEndingPoint(end.x, end.y);
}

void Arrow::update() {
    if(isMoving){
        updatePos();
        m_end = pos;
    }
    sf::Vector2f diff = m_end - m_start;
    float length = std::sqrt(diff.x * diff.x + diff.y * diff.y)-m_triangleSize;
    float angle = std::atan2(diff.y, diff.x) * 180.f / M_PI;
    m_rect.setPosition(m_start);
    m_rect.setRotation(angle);
    m_rect.setSize(sf::Vector2f(length, m_thickness));
    m_rect.setOrigin(0.f, m_thickness / 2.f);
//    m_triangle.setOrigin(-length, 0.f);
    m_triangle.setRotation(angle);
    m_triangle.setPosition(m_end);
//    std::cout<<m_start.x<<' '<<m_rect.getPosition().x<<' '<<m_rect.getGlobalBounds().left<<'\n';
}

void Arrow::draw(sf::RenderWindow &window) {
    update();
    window.draw(m_rect);
    window.draw(m_triangle);
}


