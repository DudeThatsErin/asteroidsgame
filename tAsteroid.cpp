#include <random>
#include <iostream>
#include <type_traits>
#include "tAsteroid.h"
static std::mt19937 gen(std::random_device{}());

tAsteroid::tAsteroid(sf::Vector2f direction, sf::Vector2f position)
    : Entity(position, 0), direction(direction), array(sf::LinesStrip, 19), tLife() {
    array[0].position = sf::Vector2f(90, 10);
    array[1].position = sf::Vector2f(70, 25);
    array[2].position = sf::Vector2f(85, 40);
    array[3].position = sf::Vector2f(50, 60);
    array[4].position = sf::Vector2f(20, 60);
    array[5].position = sf::Vector2f(-20, 45);
    array[6].position = sf::Vector2f(-20, 35);
    array[7].position = sf::Vector2f(-15, 25);
    array[8].position = sf::Vector2f(-25, 15);
    array[9].position = sf::Vector2f(-15, 5);
    array[10].position = sf::Vector2f(-30, -10);
    array[11].position = sf::Vector2f(-30, -35);
    array[12].position = sf::Vector2f(-15, -45);
    array[13].position = sf::Vector2f(0, -35);
    array[14].position = sf::Vector2f(20, -50);
    array[15].position = sf::Vector2f(55, -50);
    array[16].position = sf::Vector2f(65, -40);
    array[17].position = sf::Vector2f(80, -25);
    array[18].position = array[0].position; // closes the asteroid; without this the asteroid has an open spot; only needed for LinesStrip

    for (size_t i = 0; i < array.getVertexCount(); i++) {
        array[i].color = sf::Color::White;
    }
}

void tAsteroid::update(float deltaTime)
{
    tLife += deltaTime;
    position += tASTEROID_SPEED * direction * deltaTime;
    angle += tASTEROID_SPIN * deltaTime;

    // bounce asteroids on edges of screen
    if (position.x < tASTEROID_W / 2.0f) {
        direction.x = abs(direction.x);
    }
    else if (position.x > SCREEN_WIDTH + tASTEROID_W / 2.0f) {
        direction.x = -abs(direction.x);
    }

    if (position.y < tASTEROID_H / 2.0f) {
        direction.y = abs(direction.y);
    }
    else if (position.y > SCREEN_HEIGHT + tASTEROID_H / 2.0f) {
        direction.y = -abs(direction.y);
    }
}

void tAsteroid::render(sf::RenderWindow& window)
{
    window.draw(array, sf::Transform().translate(position).rotate(angle));
}

const sf::VertexArray& tAsteroid::getVertexArray() const
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
sf::Vector2f tAsteroid::getRandomDirection()
{
    float angle = generate(0.0f, 2.0f * M_PI);
    return sf::Vector2f(cos(angle), sin(angle));
}

// makes asteroids spawn at random positions
sf::Vector2f tAsteroid::getRandomPosition()
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