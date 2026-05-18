#include "../lib/Line.hpp"
Line::Line(Point& p1_inp, Point& p2_inp, float thickness_inp, float targetLength_inp)
    : p1(p1_inp), p2(p2_inp), thickness(thickness_inp), targetLength(targetLength_inp) {
    line.setFillColor(sf::Color::Blue);
    line.setSize(sf::Vector2f(targetLength, thickness));
    //line.setOrigin(sf::Vector2f(0.f, thickness / 2.f));
}

sf::Vector2f Line::getDirection() const {
    return p2.get_Position() - p1.get_Position();
}

float Line::getLength() const {
    sf::Vector2f d = getDirection();
    return std::sqrt(d.x * d.x + d.y * d.y);
}

void Line::update() {
    sf::Vector2f p1pos = p1.get_Position();
    sf::Vector2f p2pos = p2.get_Position();

    sf::Vector2f delta = p2pos - p1pos;
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (dist == 0.f) return;
    sf::Vector2f n = delta / dist;
    float error = dist - targetLength;
    float strength = 1.f;

    sf::Vector2f force = n * (error * strength);
    sf::Vector2f v1 = p1.get_Velocity();
    sf::Vector2f v2 = p2.get_Velocity();

    p1.set_Velocity(v1 + force);
    p2.set_Velocity(v2 - force);
    float correction_strength = 0.1f;

    sf::Vector2f correction = n * (error * correction_strength);

    p1.set_Position(p1pos + correction);
    p2.set_Position(p2pos - correction);

}

void Line::draw(sf::RenderWindow& window) {
    window.draw(line);
}