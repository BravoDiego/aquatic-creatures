// Joint.cpp

#include "../lib/Joint.hpp"
#include "../lib/Point.hpp"
#include "../lib/Utils.hpp"

#include <cmath>

Joint::Joint(
    int a,
    int b,
    int c,

    float strength,
    float minAngle,
    float maxAngle,

    float speed,
    float stiffness,

    bool muscle
)

    : a(a),
      b(b),
      c(c),

      strength(strength),
      minAngle(minAngle),
      maxAngle(maxAngle),

      speed(speed),
      stiffness(stiffness),

      muscle(muscle)
{
    // angle neutre
    baseAngle =
        (minAngle + maxAngle) * 0.5f;

    // paramètres évolutifs
    frequency =
        80.f +
        static_cast<float>(rand()) /
        RAND_MAX * 5.f;

    phase =
        static_cast<float>(rand()) /
        RAND_MAX * 6.28318f;

    amplitude =
        (maxAngle - minAngle) * 0.5f;

    damping = 1.0f;
}
void Joint::update(std::vector<Point>& points, float time)
{
    // que du caca
}