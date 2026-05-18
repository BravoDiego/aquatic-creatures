// Joint.hpp
#ifndef JOINT_HPP
#define JOINT_HPP

#include <SFML/System.hpp>
#include <cmath>
#include "Utils.hpp"
#include "Point.hpp"

class Joint {
public:
    Joint(Point& a, Point& b, Point& c,
          float minAngle = 0.0f, float maxAngle = 3.14f,
          float speed = 1.0f, float stiffness = 0.1f, float phase = 0.f);

    void update(float dt, float elapsedTime);

private:
    Point& A;
    Point& B;
    Point& C;
    float minAngle;
    float maxAngle;
    float speed;
    float stiffness;
    float phase;
};

#endif
