#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "Point.hpp"

class Line {

public:
    Line(
        int p1,
        int p2,
        float targetLength,
        float thickness = 6.f
    );

    void update(std::vector<Point>& points);

    void draw(
        sf::RenderWindow& window,
        std::vector<Point>& points
    );

    int getP1() const;
    int getP2() const;

private:
    int p1;
    int p2;
    float targetLength;
    float thickness;
    sf::RectangleShape line;
};

#endif