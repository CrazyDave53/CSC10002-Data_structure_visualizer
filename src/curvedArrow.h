#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_CURVEDARROW_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_CURVEDARROW_H

#include <SFML/Graphics.hpp>
#include <cmath>

class CurvedArrow {
public:
    CurvedArrow(sf::Vector2f start, sf::Vector2f end);

    void setThickness(float thickness);
    void setTriangleSize(float size);
    void setStart(sf::Vector2f start);
    void setEnd(sf::Vector2f end);
    void setOpacity(float opacity);
    void setCurvature(float curvature);

    void moveEnd(sf::Vector2f end, float time);
    void draw(sf::RenderWindow& window);

    void update();

private:
    sf::RectangleShape m_rect;
    sf::CircleShape m_circle;
    sf::ConvexShape m_triangle;
    sf::VertexArray m_curve;
    sf::Vector2f m_start;
    sf::Vector2f m_end;
    float m_thickness;
    float m_triangleSize;
    float m_curvature;
    bool m_isMoving;
    sf::Vector2f pos;
    float arrowAngle;
    float arrowLength;
    float arrowTheta;
    sf::Vector2f arrowTail;

    void updatePos(float t);
    void updateCurve();
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_CURVEDARROW_H
