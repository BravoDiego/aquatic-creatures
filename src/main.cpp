#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include "../lib/Point.hpp"
#include "../lib/Line.hpp"
#include "../lib/Joint.hpp"

int main() {
    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Jeu à 50 FPS");
    window.setFramerateLimit(50);

    std::vector<Point> points;
    std::vector<Line> lines;
    std::vector<Joint> joints;

    points.emplace_back(sf::Vector2f(150, 286), sf::Vector2f(0, 0));
    points.emplace_back(sf::Vector2f(200, 200), sf::Vector2f(0, 0));
    points.emplace_back(sf::Vector2f(250, 280), sf::Vector2f(0, 0));
    points.emplace_back(sf::Vector2f(300, 200), sf::Vector2f(0, 0));
    points.emplace_back(sf::Vector2f(100, 200), sf::Vector2f(0, 0));
    lines.emplace_back(points[0], points[1]);
    lines.emplace_back(points[1], points[2]);
    lines.emplace_back(points[3], points[4]);
    //lines.emplace_back(points[3], points[4]);

    joints.emplace_back(points[0], points[1], points[2]);

    
    // Création de la vue (caméra)
    sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));
    const float cameraSpeed = 200.f;
    float zoomLevel = 1.f;
    // Boucle principale
    sf::Clock clock; // Pour calculer le temps écoulé
    while (window.isOpen()) {
        // Gestion des événements
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Gestion des entrées utilisateur (déplacement de la caméra)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            zoomLevel *= 0.95f; // Zoom avant
            view.setSize(window.getDefaultView().getSize());
            view.zoom(zoomLevel);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            zoomLevel *= 1.05f; // Zoom arrière
            view.setSize(window.getDefaultView().getSize());
            view.zoom(zoomLevel);
        }

        float deltaTime = clock.restart().asSeconds(); // Temps écoulé depuis le dernier frame
        sf::Vector2f cameraMovement(0.f, 0.f); // Vecteur de déplacement de la caméra
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            cameraMovement.x -= cameraSpeed * deltaTime * zoomLevel;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            cameraMovement.x += cameraSpeed * deltaTime * zoomLevel;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            cameraMovement.y -= cameraSpeed * deltaTime * zoomLevel;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            cameraMovement.y += cameraSpeed * deltaTime * zoomLevel;

        // Déplacement de la caméra
        view.move(cameraMovement);
        window.setView(view);
    
        // Mise à jour des points et de la lign

        static float elapsed = 0.f;
        elapsed += deltaTime;

        for (auto& point : points) {
            point.update(deltaTime);
        }

        // Mettre à jour les liens
        for (auto& line : lines) {
            line.update();
        }

        for (auto& joint : joints) {
            joint.update(deltaTime, elapsed);
        }

        for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = i + 1; j < points.size(); ++j) {
                checkCollision(points[i], points[j]);
            }
        }
        // Effacer la fenêtre

        window.clear(sf::Color::White);
        for (auto& line : lines) {
            line.draw(window);
        }
        for (auto& point : points) {
            point.draw(window);
        }
        // Afficher les éléments dessinés
        window.display();
    }

    return 0;
}