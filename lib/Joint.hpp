// Joint.hpp

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Point;

class Joint
{
public:

    int a;
    int b;
    int c;

    // paramètres physiques
    float strength;
    float stiffness;

    // limites articulation
    float minAngle;
    float maxAngle;

    // muscle
    bool muscle;

    float speed;
    float frequency;
    float phase;

    float amplitude;
    float baseAngle;

    // damping
    float damping;

    Joint(
        int a,
        int b,
        int c,

        float strength = 1.f,

        float minAngle = 1.5f,
        float maxAngle = 3.14f,

        float speed = 1.f,
        float stiffness = 0.02f,

        bool muscle = true
    );

    void update(std::vector<Point>& points, float time);
};