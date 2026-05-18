#ifndef Line_HPP
#define Line_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Point.hpp"
#include "Utils.hpp"

class Line {
    public:
        Line(Point& p1, Point& p2, float thickness = 6.f, float targetLength = 100.f);
        sf::Vector2f getDirection() const;
        float getLength() const;
        void update();
        void draw(sf::RenderWindow& window);
    private:
        float thickness; // Épaisseur du trait
        float targetLength; // Longueur cible de la ligne
        Point& p1;
        Point& p2;
        sf::RectangleShape line;
};

#endif