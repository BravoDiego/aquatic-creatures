#include "../lib/Point.hpp"

Point::Point()
    : pos(0.f, 0.f),
      vel(0.f, 0.f),
      mass(1.f)
{
    sphere.setRadius(10.f);
    sphere.setOrigin(
        sf::Vector2f(
            sphere.getRadius(),
            sphere.getRadius()
        )
    );
    sphere.setFillColor(sf::Color::Red);
}

Point::Point(
    const sf::Vector2f& position,
    const sf::Vector2f& velocity,
    float mass,
    float radius
)
    : pos(position),
      vel(velocity),
      mass(mass)
{
    sphere.setRadius(radius);

    sphere.setOrigin(
        sf::Vector2f(radius, radius)
    );

    sphere.setFillColor(sf::Color::Red);
}

void Point::update(float deltaTime)
{
    pos += vel * deltaTime;
    vel *= 0.99f; // askip faurdrait en mettre 
}

void Point::move(const sf::Vector2f& offset)
{
    pos += offset;
}

void Point::applyForce(const sf::Vector2f& force)
{
    vel += force / mass; // mass = 1kg donc osef
}

sf::Vector2f Point::get_Position() const { return pos; }

sf::Vector2f Point::get_Velocity() const { return vel; }

float Point::get_Mass() const { return mass; }

void Point::set_Position(const sf::Vector2f& position) { pos = position; }

void Point::set_Velocity(const sf::Vector2f& velocity) { vel = velocity; }

void Point::draw(sf::RenderWindow& window)
{
    sphere.setPosition(pos);
    window.draw(sphere);
}