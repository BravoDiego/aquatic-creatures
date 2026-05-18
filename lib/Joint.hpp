#ifndef JOINT_HPP
#define JOINT_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Point.hpp"

class Joint {

public:

    Joint(int a, int b, int c, float strength = 0.5f, float minAngle = 0.f, float maxAngle = 3.14f, float speed = 1.f, float stiffness = 0.5f);

    void update(std::vector<Point>& points, float dt);

private:

    int a;
    int b;
    int c;

    float strength;
    float minAngle;
    float maxAngle;
    float speed;
    float stiffness;
    float baseAngle;   // angle naturel
    float frequency;   // pour futur muscles
    float phase;
};

#endif