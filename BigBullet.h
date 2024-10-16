#pragma once
#include "Entity.h"
constexpr float tBULLET_SPEED = 500.0f;
constexpr float tSHOOT_DELAY = 0.2f;
constexpr float tBULLET_LIFE = 3.0f;

class BigBullet : public Entity {
public:
    BigBullet(sf::Vector2f position, sf::Vector2f direction);

    void update(float deltaTime) override;

    void render(sf::RenderWindow& window) override;
private:
    sf::Vector2f direction;
    sf::CircleShape shape;
    sf::Color color;
    float lifeTime;
};
