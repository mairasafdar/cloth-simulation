#include "particle.h"
#include <SFML/Graphics.hpp> 
#include <vector>



const int WIDTH = 1080;
const int HEIGHT = 640;
const float PARTICLE_RADIUS = 30.0f;
const float GRAVITY = 10.0f;
const float TIME_STEP = 0.01f;


int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "C++ Cloth Simulation");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    particles.emplace_back(WIDTH / 2, HEIGHT / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // apply gravity and Update particles
        for (auto& particle : particles) {
            particle.applyForce(sf::Vector2f(0.0f, GRAVITY)); // gravity
            particle.update(TIME_STEP); 
        }

        window.clear(sf::Color::Black);

        // Drawing code goes here - draw particles as balls
        for (const auto& particle : particles) {
            sf::CircleShape circle(PARTICLE_RADIUS);
            circle.setFillColor(sf::Color::White);
            //circle.setOrigin(PARTICLE_RADIUS, PARTICLE_RADIUS);
            circle.setPosition(particle.position);
            window.draw(circle);
        }

        window.display();
    }

   
}
