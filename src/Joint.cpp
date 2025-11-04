// Joint.cpp
#include "../lib/Joint.hpp"
#include <cmath>

Joint::Joint(Point& a, Point& b, Point& c,
             float minAngle, float maxAngle,
             float speed, float stiffness, float phase)
    : A(a), B(b), C(c),
      minAngle(minAngle), maxAngle(maxAngle),
      speed(speed), stiffness(stiffness), phase(phase)
{}

void Joint::update(float dt, float elapsedTime) {
    // --- 1. Calcul de l'angle actuel
    sf::Vector2f AB = A.get_Position() - B.get_Position();
    sf::Vector2f CB = C.get_Position() - B.get_Position();

    float angle = std::atan2(AB.x * CB.y - AB.y * CB.x,
                             AB.x * CB.x + AB.y * CB.y);

    // --- 2. Calcul de l'angle cible (oscillation)
    float targetAngle = (minAngle + maxAngle) / 2.f
        + (maxAngle - minAngle) / 2.f * std::sin(speed * elapsedTime + phase);

    // --- 3. Différence
    float delta = angle - targetAngle;

    // Normalisation -π..π
    if (delta > M_PI) delta -= 2 * M_PI;
    if (delta < -M_PI) delta += 2 * M_PI;

    // --- 4. Appliquer une rotation légère vers l’angle cible
    float s = delta * stiffness;

    auto rotate = [](sf::Vector2f p, sf::Vector2f center, float s) {
        float x = p.x - center.x;
        float y = p.y - center.y;
        float newX = x * cos(s) - y * sin(s);
        float newY = x * sin(s) + y * cos(s);
        return sf::Vector2f(center.x + newX, center.y + newY);
    };

    A.set_Position(rotate(A.get_Position(), B.get_Position(), +s));
    C.set_Position(rotate(C.get_Position(), B.get_Position(), -s));
}
