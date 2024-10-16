#pragma once
#include "Entity.h"
#include <type_traits>

constexpr float tASTEROID_W = 90.0f;
constexpr float tASTEROID_H = 80.0f;
constexpr float tASTEROID_SPIN = 25.0f;
constexpr float tASTEROID_SPEED = 140.0f;
constexpr float tASTEROID_SPAWN_TIME = 2.0f;
constexpr float tASTEROID_HIT_TIME = 50.0f;
constexpr float tASTEROID_MAX_GEN = 1.0f;

class tAsteroid : public Entity {
public:
    tAsteroid(sf::Vector2f direction = tAsteroid::getRandomDirection(), sf::Vector2f position = tAsteroid::getRandomPosition());

    void update(float deltaTime) override;

    void render(sf::RenderWindow& window) override;

    const sf::VertexArray& getVertexArray() const;

    // moves asteroids in random directions
    static sf::Vector2f getRandomDirection();

    // spawns asteroids at random positions
    static sf::Vector2f getRandomPosition();

    float gGetLife() { return tLife; }

private:
    sf::VertexArray array;
    sf::Vector2f direction;

    float tLife;
};