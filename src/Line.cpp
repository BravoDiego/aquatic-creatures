#include "../lib/Line.hpp"

Line::Line(
    int p1,
    int p2,
    float targetLength,
    float thickness
)
    : p1(p1),
      p2(p2),
      targetLength(targetLength),
      thickness(thickness)
{
    line.setFillColor(sf::Color::Blue);
    line.setSize(
        sf::Vector2f(targetLength, thickness)
    );
    line.setOrigin(
        sf::Vector2f(0.f, thickness / 2.f)
    );
}

void Line::update(std::vector<Point>& points)
{
    Point& A = points[p1];
    Point& B = points[p2];

    sf::Vector2f delta =
        B.get_Position() - A.get_Position();

    float dist =
        std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (dist == 0.f)
        return;

    // direction normalisée
    sf::Vector2f n = delta / dist;
    float error = dist - targetLength;
    float stiffness = 4.0f;
    sf::Vector2f force =
        n * (error * stiffness);

    // appliquer inertie
    A.applyForce(force);
    B.applyForce(-force);
    float correctionStrength = 0.5f;
    sf::Vector2f correction =
        n * (error * correctionStrength);
    A.move(correction);
    B.move(-correction);
}

void Line::draw(
    sf::RenderWindow& window,
    std::vector<Point>& points
)
{
    Point& A = points[p1];
    Point& B = points[p2];

    sf::Vector2f delta =
        B.get_Position() - A.get_Position();

    float length =
        std::sqrt(delta.x * delta.x + delta.y * delta.y);

    line.setPosition(A.get_Position());

    line.setSize(
        sf::Vector2f(length, thickness)
    );

    float angle =
        std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;

    line.setRotation(
        sf::degrees(angle)
    );
    window.draw(line);
}

int Line::getP1() const { return p1; }

int Line::getP2() const { return p2; }