#include "Asteroid.h"
#include <random>
#include <iostream>
#include <type_traits>
static std::mt19937 gen(std::random_device{}());

Asteroid::Asteroid(sf::Vector2f direction, sf::Vector2f position)
    : Entity(position, 0), direction(direction), array(sf::LinesStrip, 19), life() {
    array[0].position = sf::Vector2f(40, 5);
    array[1].position = sf::Vector2f(30, 10);
    array[2].position = sf::Vector2f(35, 20);
    array[3].position = sf::Vector2f(25, 30);
    array[4].position = sf::Vector2f(5, 30);
    array[5].position = sf::Vector2f(-5, 25);
    array[6].position = sf::Vector2f(-5, 20);
    array[7].position = sf::Vector2f(-10, 15);
    array[8].position = sf::Vector2f(-15, 10);
    array[9].position = sf::Vector2f(-5, 5);
    array[10].position = sf::Vector2f(-15, -5);
    array[11].position = sf::Vector2f(-15, -15);
    array[12].position = sf::Vector2f(-5, -25);
    array[13].position = sf::Vector2f(0, -20);
    array[14].position = sf::Vector2f(10, -25);
    array[15].position = sf::Vector2f(30, -25);
    array[16].position = sf::Vector2f(35, -20);
    array[17].position = sf::Vector2f(40, -15);
    array[18].position = array[0].position; // closes the asteroid; without this the asteroid has an open spot; only needed for LinesStrip

    for (size_t i = 0; i < array.getVertexCount(); i++) {
        array[i].color = sf::Color::White;
    }
}

void Asteroid::update(float deltaTime)
{
    life += deltaTime;
    position += ASTEROID_SPEED * direction * deltaTime;
    angle += ASTEROID_SPIN * deltaTime;

    // bounce asteroids on edges of screen
    if (position.x < ASTEROID_W / 2.0f) {
        direction.x = abs(direction.x);
    }
    else if (position.x > SCREEN_WIDTH - ASTEROID_W / 2.0f) {
        direction.x = -abs(direction.x);
    }

    if (position.y < ASTEROID_H / 2.0f) {
        direction.y = abs(direction.y);
    }
    else if (position.y > SCREEN_HEIGHT - ASTEROID_H / 2.0f) {
        direction.y = -abs(direction.y);
    }
}

void Asteroid::render(sf::RenderWindow& window)
{
    window.draw(array, sf::Transform().translate(position).rotate(angle));
}

const sf::VertexArray& Asteroid::getVertexArray() const
{
    return array;
}

template<typename T>
T generate(T lower, T upper)
{
    if constexpr (std::is_floating_point_v<T>)
    {
        return std::uniform_real_distribution<T>{ lower, upper }(gen);
    }
    else
    {
        return std::uniform_int_distribution<T>{ lower, upper }(gen);
    }
}

// makes asteroids go in random directions
sf::Vector2f Asteroid::getRandomDirection()
{
    float angle = generate(0.0f, 2.0f * M_PI);
    return sf::Vector2f(cos(angle), sin(angle));
}

// makes asteroids spawn at random positions
sf::Vector2f Asteroid::getRandomPosition()
{
    int side = generate(0, 3);
    float xAxis, yAxis;
    if (side == 0) {
        xAxis = 0;
        yAxis = generate(0.0f, SCREEN_HEIGHT);
        return sf::Vector2f(xAxis, yAxis);
    }
    else if (side == 1)
    {
        xAxis = SCREEN_WIDTH;
        yAxis = generate(0.0f, SCREEN_HEIGHT);
        return sf::Vector2f(xAxis, yAxis);
    }
    else if (side == 2) {
        xAxis = 0;
        yAxis = generate(0.0f, SCREEN_HEIGHT);
        return sf::Vector2f(xAxis, yAxis);
    }
    else if (side == 3)
    {
        xAxis = SCREEN_WIDTH;
        yAxis = generate(0.0f, SCREEN_HEIGHT);
        return sf::Vector2f(xAxis, yAxis);
    }

    return sf::Vector2f(0, 0);
}
