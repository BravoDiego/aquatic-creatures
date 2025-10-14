#include "../lib/Line.hpp"
Line::Line(Point& p1_inp, Point& p2_inp, float thickness_inp, float targetLength_inp)
    : p1(p1_inp), p2(p2_inp), thickness(thickness_inp), targetLength(targetLength_inp) {
    line.setFillColor(sf::Color::Blue);
    update();
}

sf::Vector2f Line::getDirection() const {
    return p2.get_Position() - p1.get_Position();
}

float Line::getLength() const {
    sf::Vector2f d = getDirection();
    return std::sqrt(d.x * d.x + d.y * d.y);
}

void Line::update() {
    sf::Vector2f delta = getDirection();
    float currentLength = getLength();
    if (currentLength == 0) return;

    // --- 1. Correction de position (distance)
    float diff = (currentLength - targetLength) / currentLength;
    sf::Vector2f correction = delta * 0.5f * diff;

    // Appliquer la correction aux positions
    p1.move(correction);
    p2.move(-correction);

    // --- 2. Correction de vitesse (stabilisation)
    sf::Vector2f v1 = p1.get_Velocity();
    sf::Vector2f v2 = p2.get_Velocity();

    // Vitesse relative
    sf::Vector2f relVel = v2 - v1;

    // Projection de la vitesse relative sur l’axe du lien
    float dotProd = (relVel.x * delta.x + relVel.y * delta.y) / currentLength;
    sf::Vector2f direction = delta / currentLength;
    sf::Vector2f correctionVel = direction * (dotProd * 0.5f);

    // Enlever uniquement la composante radiale (évite oscillations)
    p1.set_Velocity(v1 + correctionVel);
    p2.set_Velocity(v2 - correctionVel);

    // --- 3. Mettre à jour l’objet graphique
    line.setSize({currentLength, thickness});
    line.setOrigin({0.f, thickness / 2.f});
    line.setPosition(p1.get_Position());
    float angle = std::atan2(delta.y, delta.x);
    line.setRotation(sf::radians(angle));
}

void Line::draw(sf::RenderWindow& window) {
    window.draw(line);
}