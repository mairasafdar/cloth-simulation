#include "particle.h"
#include <SFML/Graphics.hpp> 
#include <vector>
#include "constraint.h"


const int WIDTH = 1080;
const int HEIGHT = 640;
const float PARTICLE_RADIUS = 30.0f;
const float GRAVITY = 10.0f;
const float TIME_STEP = 0.1f;

const int ROWS = 10;
const int COLS = 10;
const float SPACING = 30.0f;


int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "C++ Cloth Simulation");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    std::vector<Constraint> constraints;

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            float x = col * SPACING + WIDTH/3;
            float y = row * SPACING + HEIGHT/3;
            bool pinned = (row == 0);
            particles.emplace_back(x, y, pinned);
        }
    }
    // Initialize constraints
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (col < COLS - 1) {
                // Horizontal constraint
                constraints.emplace_back(&particles[row * COLS + col], &particles[row * COLS + col + 1]);
            }
            if (row < ROWS - 1) {
                // Vertical constraint
                constraints.emplace_back(&particles[row * COLS + col], &particles[(row + 1) * COLS + col]);
            }
        }
    }
    

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
