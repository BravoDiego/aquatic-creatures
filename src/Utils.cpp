#include "../lib/Utils.hpp"

float dot(const sf::Vector2f& a, const sf::Vector2f& b) {
    return a.x * b.x + a.y * b.y;
}

float magnitude(const sf::Vector2f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

void checkCollision(Point& p1, Point& p2) {
    float minDistance = 15.f; // Distance minimale entre les points
    sf::Vector2f delta = p2.get_Position() - p1.get_Position();
    float distance = magnitude(delta);

    if (distance < minDistance && distance > 0) {
        sf::Vector2f direction = delta / distance;
        sf::Vector2f correction = direction * (minDistance - distance) / 2.f;
        p1.move(-correction);
        p2.move(correction);
    }
}