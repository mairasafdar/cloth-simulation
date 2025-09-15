#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
    public:
    sf::Vector2f position;
    sf::Vector2f previous_position;
    sf::Vector2f acceleration;

    Particle(float x, float y) 
        : position(x, y), previous_position(x, y), acceleration(x, y) {}

};

#endif // PARTICLE_H