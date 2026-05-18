#include "../lib/Point.hpp"

Point::Point(sf::Vector2f pos, sf::Vector2f vel)
    : pos(pos), vel(vel) 
{
    sphere.setRadius(10.f);
    sphere.setFillColor(sf::Color::Red);
    sphere.setOrigin({10.f, 10.f});
    sphere.setPosition(pos);
}

void Point::update(float deltaTime) {
    pos += vel * deltaTime;
}

void Point::move(const sf::Vector2f& offset) {
    pos += offset;
}

void Point::applyForce(const sf::Vector2f& force) {
    vel += force;
}

void Point::set_Velocity(const sf::Vector2f& velocity) {
    vel = velocity;
}
void Point::set_Position(const sf::Vector2f& position) {
    pos = position;
}

sf::Vector2f Point::get_Velocity() { return vel; }

sf::Vector2f Point::get_Position() { return pos; }

void Point::draw(sf::RenderWindow& window) {
    sphere.setOrigin({10.f, 10.f});
    sphere.setPosition(pos);
    sphere.setFillColor(sf::Color::Red);
    window.draw(sphere);
}
