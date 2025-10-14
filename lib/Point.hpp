#ifndef Point_HPP
#define Point_HPP

#include <SFML/Graphics.hpp>

class Point {
    public:
        Point();
        Point(sf::Vector2f pos, sf::Vector2f vel);
        // void print();
        void update(float deltaTime);
        void move(const sf::Vector2f& offset);
        void apply_Force(const sf::Vector2f& force);
        void set_Velocity(const sf::Vector2f& velocity);
        void set_Position(const sf::Vector2f& position);
        sf::Vector2f get_Velocity();
        sf::Vector2f get_Position();
        void draw(sf::RenderWindow& window);
    private:
        sf::Vector2f pos;
        sf::Vector2f vel;
        sf::CircleShape sphere;
};



#endif