#include "particle.h"
#include <SFML/Graphics.hpp> 
#include <vector>
#include "constraint.h"


const int WIDTH = 1080;
const int HEIGHT = 640;
const float PARTICLE_RADIUS = 30.0f;
const float GRAVITY = 10.0f;
const float TIME_STEP = 0.1f;


int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "C++ Cloth Simulation");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    particles.emplace_back(WIDTH / 2 - 50, HEIGHT / 2 - 50);
    particles.emplace_back(WIDTH / 2 + 50, HEIGHT / 2 - 50);
    particles.emplace_back(WIDTH / 2 - 50, HEIGHT / 2 + 50);
    particles.emplace_back(WIDTH / 2 + 50, HEIGHT / 2 + 50);

    std::vector<Constraint> constraints;
    constraints.emplace_back(&particles[0], &particles[1]);
    constraints.emplace_back(&particles[1], &particles[3]);
    constraints.emplace_back(&particles[3], &particles[2]);
    constraints.emplace_back(&particles[2], &particles[0]);
    constraints.emplace_back(&particles[0], &particles[3]);
    constraints.emplace_back(&particles[1], &particles[2]); //connecting sticks between each point

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
            particle.constrainToBounds(WIDTH, HEIGHT, PARTICLE_RADIUS); 
        }

        for (size_t i = 0; i < 5; ++i) { // iterate multiple times for stability
            for (auto& constraint : constraints) {
                constraint.satisfy();
            }
        }

        window.clear(sf::Color::Black);

        // Drawing code goes here - draw particles as balls
        for (const auto& particle : particles) {
            sf::CircleShape circle(PARTICLE_RADIUS);
            circle.setFillColor(sf::Color::White);
            circle.setOrigin(PARTICLE_RADIUS, PARTICLE_RADIUS);
            circle.setPosition(particle.position);
            window.draw(circle);
        }
        //drawing constraints as lines
        for (const auto& constraint : constraints) {
            sf::Vertex line[] =
            {
                sf::Vertex(constraint.p1->position, sf::Color::White),
                sf::Vertex(constraint.p2->position, sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }

   
}
