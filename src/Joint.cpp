#include "../lib/Joint.hpp"
#include "../lib/Utils.hpp"

Joint::Joint(int a, int b, int c, float strength, float minAngle, float maxAngle, float speed, float stiffness)
    : a(a), b(b), c(c), strength(strength), minAngle(minAngle), maxAngle(maxAngle), speed(speed), stiffness(stiffness)
{
    baseAngle = 0.f; // angle neutre (180°)
    frequency = 1.f + static_cast<float>(rand()) / RAND_MAX * 2.f;
    phase = 0.f; //static_cast<float>(rand()) / RAND_MAX * 6.28f;
}

void Joint::update(std::vector<Point>& points, float dt)
{
    Point& A = points[a];
    Point& B = points[b];
    Point& C = points[c];
    sf::Vector2f BA =
        A.get_Position() - B.get_Position();

    sf::Vector2f BC =
        C.get_Position() - B.get_Position();

    float lenBA = magnitude(BA);
    float lenBC = magnitude(BC);

    if (lenBA == 0 || lenBC == 0)
        return;

    sf::Vector2f dirBA = BA / lenBA;
    sf::Vector2f dirBC = BC / lenBC;

    // angle actuel
    float cosAngle =
        clampf(
            dot_product(dirBA, dirBC),
            -1.f,
            1.f
        );

    float angle = std::acos(cosAngle);

    // angle cible
    float mid =
        (minAngle + maxAngle) * 0.5f;

    float amp =
        (maxAngle - minAngle) * 0.5f;

    float targetAngle =
        mid +
        amp * std::sin(speed * dt + phase);

    // erreur
    float error =
        targetAngle - angle;

    // vecteurs tangents
    sf::Vector2f tangentA(
        -dirBA.y,
         dirBA.x
    );

    sf::Vector2f tangentC(
         dirBC.y,
        -dirBC.x
    );

    // force faible et stable
    sf::Vector2f forceA =
        tangentA * error * stiffness;

    sf::Vector2f forceC =
        tangentC * error * stiffness;

    A.applyForce(forceA);
    C.applyForce(forceC);

    // conservation mouvement
    B.applyForce(-(forceA + forceC));
}