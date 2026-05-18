#ifndef POINT_HPP
#define POINT_HPP

#include <SFML/Graphics.hpp>

class Point {

public:
    Point();

    Point(
        const sf::Vector2f& position,
        const sf::Vector2f& velocity = sf::Vector2f(0.f, 0.f),
        float mass = 1.f,
        float radius = 10.f
    );

    void update(float deltaTime);
    void move(const sf::Vector2f& offset);
    void applyForce(const sf::Vector2f& force);

    sf::Vector2f get_Position() const;
    sf::Vector2f get_Velocity() const;
    float get_Mass() const;
    void set_Position(const sf::Vector2f& position);
    void set_Velocity(const sf::Vector2f& velocity);
    void draw(sf::RenderWindow& window);

private:
    float mass;
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::CircleShape sphere;
};

#endif