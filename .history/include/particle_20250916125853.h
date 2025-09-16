#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
    public:
    sf::Vector2f position;
    sf::Vector2f previous_position;
    sf::Vector2f acceleration;
bool is_pinned;

    Particle(float x, float y, bool pinned = false) : position(x, y), previous_position(x, y),
                                acceleration(0, 0), is_pinned(pinned) {}

    void applyForce(const sf::Vector2f& force) {
        if (!is_pinned) {
            acceleration += force;
        }
    }
    void update(float time_step) {
        // verlet integration
        sf::Vector2f velocity = position - previous_position;
        previous_position = position;
        position += velocity + acceleration * time_step * time_step;
        acceleration = sf::Vector2f(0, 0); // reset acceleration after update
    }

    void constrainToBounds(float width, float height, float radius) {
        if (position.x < radius) position.x = radius;
        if (position.x > width - radius) position.x = width - radius;
        if (position.y < radius) position.y = radius;
        if (position.y > height - radius) position.y = height - radius;
    }
};

#endif // PARTICLE_H