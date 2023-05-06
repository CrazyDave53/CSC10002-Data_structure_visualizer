

#include "curvedArrow.h"

CurvedArrow::CurvedArrow(sf::Vector2f start, sf::Vector2f end)
        : m_thickness(5.f), m_triangleSize(15.f), m_curvature(0.25f), m_start(start), m_end(end), m_isMoving(false), pos(start), arrowTail(end)
{
    update();
}

void CurvedArrow::setThickness(float thickness)
{
    m_thickness = thickness;
    update();
}

void CurvedArrow::setTriangleSize(float size)
{
    m_triangleSize = size;
    update();
}

void CurvedArrow::setStart(sf::Vector2f start){
    m_start = start;
    update();
}

void CurvedArrow::setEnd(sf::Vector2f end) {
    arrowTail = end;
    update();
}

void CurvedArrow::setOpacity(float opacity) {
    m_rect.setFillColor(sf::Color(255, 255, 255, opacity));
    m_triangle.setFillColor(sf::Color(255, 255, 255, opacity));
}

void CurvedArrow::setCurvature(float curvature) {
    m_curvature = curvature;
    update();
}

void CurvedArrow::moveEnd(sf::Vector2f end, float time) {
    pos = m_start;
    arrowTail = end;
    m_isMoving = true;
    sf::Clock clock;
    float elapsed = 0.f;
    while (elapsed < time) {
        elapsed = clock.getElapsedTime().asSeconds();
        float t = elapsed / time;
        updatePos(t);
        m_end = pos;
        update();
    }
    m_isMoving = false;
}

void CurvedArrow::draw(sf::RenderWindow& window)
{
    // Create the curve vertex array
    sf::VertexArray curve(sf::LineStrip, m_curve.getVertexCount());
    for (int i = 0; i < m_curve.getVertexCount(); ++i)
    {
        curve[i] = sf::Vertex(m_curve[i]);
        curve[i].color = sf::Color::White;
    }

    // Create the arrow vertex array
    sf::VertexArray arrow(sf::Triangles, 3);
    arrow[0] = sf::Vertex(m_end, sf::Color::White);
    arrow[1] = sf::Vertex(arrowTail, sf::Color::White);
    arrow[2] = sf::Vertex(sf::Vector2f(arrowTail.x - m_triangleSize * std::cos(arrowTheta * M_PI / 180.f),
                                       arrowTail.y - m_triangleSize * std::sin(arrowTheta * M_PI / 180.f)),
                          sf::Color::White);

    // Draw the arrow and curve
    window.draw(curve);
    window.draw(arrow);
}






void CurvedArrow::update() {
    sf::Vector2f diff = arrowTail - m_start;
    arrowLength = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    arrowAngle = std::atan2(diff.y, diff.x) * 180.f / M_PI;
    arrowTheta = arrowAngle - 90.f;
    float distToCurvePoint = arrowLength * m_curvature;
    float angleToCurvePoint = arrowAngle + 90.f;
    float xCurvePoint = arrowTail.x - std::cos(angleToCurvePoint * M_PI / 180.f) * distToCurvePoint;
    float yCurvePoint = arrowTail.y - std::sin(angleToCurvePoint * M_PI / 180.f) * distToCurvePoint;
    float xCurvePos = m_start.x + (xCurvePoint - m_start.x) * m_curvature;
    float yCurvePos = m_start.y + (yCurvePoint - m_start.y) * m_curvature;

    float dx = arrowLength * std::cos(arrowTheta * M_PI / 180.f);
    float dy = arrowLength * std::sin(arrowTheta * M_PI / 180.f);

    m_triangle.setPointCount(3);
    m_triangle.setPoint(0, arrowTail);
    m_triangle.setPoint(1, sf::Vector2f(arrowTail.x + dx * 0.5f - dy * 0.5f, arrowTail.y + dy * 0.5f + dx * 0.5f));
    m_triangle.setPoint(2, sf::Vector2f(arrowTail.x + dx * 0.5f + dy * 0.5f, arrowTail.y + dy * 0.5f - dx * 0.5f));
    m_triangle.setFillColor(sf::Color::White);

    m_circle.setRadius(m_thickness / 2.f);
    m_circle.setPosition(m_start);
    m_circle.setFillColor(sf::Color::White);

    float angle = std::atan2(yCurvePos - m_start.y, xCurvePos - m_start.x) * 180.f / M_PI;
    float length = std::sqrt(std::pow(yCurvePos - m_start.y, 2) + std::pow(xCurvePos - m_start.x, 2));
    m_rect.setSize(sf::Vector2f(length, m_thickness));
    m_rect.setPosition(m_start);
    m_rect.setRotation(angle);
    m_rect.setFillColor(sf::Color::White);
}

void CurvedArrow::updatePos(float t) {
    sf::Vector2f diff = arrowTail - m_start;
    arrowLength = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    arrowAngle = std::atan2(diff.y, diff.x) * 180.f / M_PI;
    arrowTheta = arrowAngle - 90.f;
    float distToCurvePoint = arrowLength * m_curvature;
    float angleToCurvePoint = arrowAngle + 90.f;
    float xCurvePoint = arrowTail.x - std::cos(angleToCurvePoint * M_PI / 180.f) * distToCurvePoint;
    float yCurvePoint = arrowTail.y - std::sin(angleToCurvePoint * M_PI / 180.f) * distToCurvePoint;
    float xCurvePos = m_start.x + (xCurvePoint - m_start.x) * t;
    float yCurvePos = m_start.y + (yCurvePoint - m_start.y) * t;
    pos = sf::Vector2f(xCurvePos, yCurvePos);
}

void CurvedArrow::updateCurve()
{
    sf::Vector2f diff = arrowTail - m_start;
    arrowLength = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    arrowAngle = std::atan2(diff.y, diff.x) * 180.f / M_PI;
    arrowTheta = arrowAngle - 90.f;
    float distToCurvePoint = arrowLength * m_curvature;
    float angleToCurvePoint = arrowAngle + 90.f;
    float xCurvePoint = arrowTail.x - std::cos(angleToCurvePoint * M_PI / 180.f) * distToCurvePoint;
    float yCurvePoint = arrowTail.y - std::sin(angleToCurvePoint * M_PI / 180.f) * distToCurvePoint;

    sf::Vector2f controlPoint(xCurvePoint, yCurvePoint);
    sf::Vector2f controlVector = controlPoint - m_start;

    m_curve[0].position = m_start;
    m_curve[1].position = m_start + controlVector * 0.5f;
    m_curve[2].position = arrowTail;

    // update thickness and color of the curve
    m_curve[0].color = m_rect.getFillColor();
    m_curve[1].color = m_rect.getFillColor();
    m_curve[2].color = m_rect.getFillColor();
    m_curve[0].color.a = 0;
    m_curve[1].color.a = 255;
    m_curve[2].color.a = 255;
}


