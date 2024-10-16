#include "BigBullet.h"
#include "Game.h"
#include "Physics.h"
#include "tAsteroid.h"

BigBullet::BigBullet(sf::Vector2f position, sf::Vector2f direction)
    : shape(4.0f), color(sf::Color::Red), direction(direction), Entity(position, 0.0f), lifeTime(tBULLET_LIFE) {}

void BigBullet::update(float deltaTime)
{
    lifeTime -= deltaTime;
    position += direction * tBULLET_SPEED * deltaTime;
    if (lifeTime <= 0.0f) {
        Game::removeList.push_back(std::find(Game::entities.begin(), Game::entities.end(), this));
    }

    for (size_t i = 0; i < Game::entities.size(); i++) {
        if (typeid(*Game::entities[i]) == typeid(tAsteroid)) {
            tAsteroid* tasteroid = dynamic_cast<tAsteroid*>(Game::entities[i]);
            sf::Transform transform = sf::Transform().translate(tasteroid->position).rotate(tasteroid->angle);

            if (physics::intersects(position, physics::getTransformed(tasteroid->getVertexArray(), transform))) {
                lifeTime = 0.0f;
                Game::removeList.push_back(std::find(Game::entities.begin(), Game::entities.end(), tasteroid));
                Game::score += 20;
            }
        }
    }
}

void BigBullet::render(sf::RenderWindow& window)
{
    window.draw(shape, sf::Transform().translate(position));
}