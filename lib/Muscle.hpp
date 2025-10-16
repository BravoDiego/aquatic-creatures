#ifndef Muscle_HPP
#define Muscle_HPP

#include <SFML/System.hpp>
#include "Point.hpp"

class Muscle {
private:
    Point& center;
    Point& p1;
    Point& p2;

    float strength;
    float activation;
    float phase;
    float frequency;

public:
    Muscle(Point& c, Point& a, Point& b, float strength = 200.f, float frequency = 2.f, float phase = 0.f);
    void update(float dt);
    void applyForces();
};

#endif