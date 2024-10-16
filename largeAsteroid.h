#pragma once
#include "Global.h"

class largeAsteroid {
public:
    largeAsteroid() : largeAsteroid({ 0,0 }, 0.0f) {}
    largeAsteroid(sf::Vector2f position, float angle) : position(position), angle(angle) {}
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~largeAsteroid();
    sf::Vector2f position;
    float angle;
};