#ifndef Utils_HPP
#define Utils_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "Point.hpp"

// Déclaration de la fonction produit scalaire
float dot(const sf::Vector2f& a, const sf::Vector2f& b);
float magnitude(const sf::Vector2f& v);
void checkCollision(Point& p1, Point& p2);
float clampf(float value, float minVal, float maxVal);

#endif
