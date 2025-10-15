#include "../lib/Muscle.hpp"
#include <cmath>

Muscle::Muscle(Point& c, Point& a, Point& b, float s, float f, float p)
    : center(c), p1(a), p2(b), strength(s), activation(0.f), phase(p), frequency(f) {}

void Muscle::update(float dt) {
    phase += frequency * dt * 2.f * 3.1415926f;
    activation = std::sin(phase); // contraction sinusoïdale
}

void Muscle::applyForces(float dt) {
    sf::Vector2f dir1 = center.get_Position() - p1.get_Position();
    sf::Vector2f dir2 = center.get_Position() - p2.get_Position();

    float len1 = std::sqrt(dir1.x * dir1.x + dir1.y * dir1.y);
    float len2 = std::sqrt(dir2.x * dir2.x + dir2.y * dir2.y);
    if (len1 == 0 || len2 == 0) return;

    dir1 /= len1;
    dir2 /= len2;

    float f = strength * activation;

    p1.applyForce(dir1 * f, dt);
    p2.applyForce(dir2 * f, dt);

    // Réaction équilibrée sur le centre
    sf::Vector2f reaction = -(dir1 * f + dir2 * f);
    center.applyForce(reaction*0.5f, dt);
}
