// Joint.cpp
#include "../lib/Joint.hpp"

Joint::Joint(Point& a, Point& b, Point& c,
             float minAngle, float maxAngle,
             float speed, float stiffness, float phase)
    : A(a), B(b), C(c),
      minAngle(minAngle), maxAngle(maxAngle),
      speed(speed), stiffness(stiffness), phase(phase)
{}

void Joint::update(float dt, float elapsedTime) {
    // --- 1. Calcul de l'angle actue
    sf::Vector2f AB = A.get_Position() - B.get_Position();
    sf::Vector2f CB = C.get_Position() - B.get_Position();

    float dot_p = dot(AB, CB);
    float magAB = magnitude(AB);
    float magCB = magnitude(CB);

    if (magAB == 0 || magCB == 0) return;

    float angle = std::acos(clampf(dot_p / (magAB * magCB), -1.f, 1.f));

    // --- 2. Calcul de l'angle cible oscillant dans [minAngle, maxAngle]
    float mid = (minAngle + maxAngle) / 2.f;
    float amp = (maxAngle - minAngle) / 2.f;

    float targetAngle = mid + amp * std::sin(speed * elapsedTime + phase);

    // --- 4. Appliquer une rotation légèe vers l’angle cible
    float s = (angle - targetAngle) * stiffness;

    auto rotate = [](sf::Vector2f p, sf::Vector2f center, float s) {
        float x = p.x - center.x;
        float y = p.y - center.y;
        float newX = x * cos(s) - y * sin(s);
        float newY = x * sin(s) + y * cos(s);
        return sf::Vector2f(center.x + newX, center.y + newY);
    };
    // --- Répartition équilibrée de la correction ---
    sf::Vector2f posA = A.get_Position();
    sf::Vector2f posB = B.get_Position();
    sf::Vector2f posC = C.get_Position();

    // A et C reçoivent 25% chacun
    posA = rotate(posA, posB, +s * 0.5f);
    posC = rotate(posC, posB, -s * 0.5f);

    // B se déplace légèreent dans la direction opposée (50%)
    sf::Vector2f centerMove = (rotate(posB, posA, -s * 0.25f) +
                               rotate(posB, posC, +s * 0.25f)) * 0.5f;
    posB = centerMove;

    A.set_Position(posA);
    B.set_Position(posB);
    C.set_Position(posC);
}
