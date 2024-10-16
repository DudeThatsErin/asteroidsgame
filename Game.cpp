#include "Game.h"
#include "Player.h"
#include "Asteroid.h"
#include "tAsteroid.h"
#include <fstream>

std::vector<Entity*> Game::entities{};
std::list <std::vector<Entity*>::const_iterator> Game::removeList{};
std::list <Entity*> Game::addList{};
float Game::asteroidSpawnTime{};
float Game::tAsteroidSpawnTime{};
float newSpawn, newSpawn2;
size_t Game::score{};
sf::Text Game::scoreText{};
sf::Font Game::font{};
sf::Text Game::gameOverText{};
sf::Text Game::continueText{};
sf::Text Game::highScoreText{};
sf::Text Game::titleText{};
sf::Text Game::menuText{};
sf::Text Game::levelText{};
sf::Text Game::playText{};
sf::SoundBuffer Game::shootSoundBuffer;
sf::SoundBuffer Game::largeShootSoundBuffer;
sf::Sound Game::shootSound{};
sf::Sound Game::largeShootSound{};
Game::State Game::state{};
size_t Game::highScore;

int getNumberOfLargeAsteroids() {
    int count = 0;
    for (size_t i = 0; i < Game::entities.size(); i++) {
        if (dynamic_cast<tAsteroid*>(Game::entities[i])) {
            ++count;
        }
    }
    return count;
}

int getNumberOfSmallAsteroids() {
    int count = 0;
    for (size_t i = 0; i < Game::entities.size(); i++) {
        if (dynamic_cast<Asteroid*>(Game::entities[i])) {
            ++count;
        }
    }
    return count;
}

void Game::init() {
    std::ifstream file("score.dat", std::ios::binary | std::ios::in);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
        file.close();
    }

    font.loadFromFile("arial.ttf");
    scoreText.setFont(font);
    scoreText.setPosition(sf::Vector2f(40, 20));
    scoreText.setCharacterSize(48);

    gameOverText.setFont(font);
    gameOverText.setPosition(sf::Vector2f(250, 350));
    gameOverText.setCharacterSize(128);
    gameOverText.setString("Game Over!");

    continueText.setFont(font);
    continueText.setPosition(sf::Vector2f(450, 550));
    continueText.setCharacterSize(24);
    continueText.setString("Press ENTER to continue...");

    highScoreText.setFont(font);
    highScoreText.setPosition(sf::Vector2f(40, 20));
    highScoreText.setCharacterSize(48);
    highScoreText.setString("High Score: " + std::to_string(highScore));

    menuText.setFont(font);
    menuText.setPosition(sf::Vector2f(420, 600));
    menuText.setCharacterSize(24);
    menuText.setString("Press ESCAPE to exit to menu...");

    titleText.setFont(font);
    titleText.setPosition(sf::Vector2f(280, 350));
    titleText.setCharacterSize(128);
    titleText.setString("ASTEROIDS");

    playText.setFont(font);
    playText.setPosition(sf::Vector2f(450, 550));
    playText.setCharacterSize(24);
    playText.setString("Press ENTER to play...");

    levelText.setFont(font);
    levelText.setPosition(sf::Vector2f(1000, 20));
    levelText.setCharacterSize(48);

    shootSoundBuffer.loadFromFile("small-shot.mp3");
    shootSound.setBuffer(shootSoundBuffer);
    largeShootSoundBuffer.loadFromFile("large_shot.mp3");
    largeShootSound.setBuffer(largeShootSoundBuffer);

    state = MENU;
}

void Game::begin() {
    state = PLAYING;
    entities.push_back(new Player());
    tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
    asteroidSpawnTime = ASTEROID_SPAWN_TIME;
    score = 0;
}

void Game::update(sf::RenderWindow& window, float deltaTime) {
    if (state == MENU) {
        window.draw(highScoreText);
        window.draw(titleText);
        window.draw(playText);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            begin();
        }
        return;
    }
    Game::addList.clear();
    Game::removeList.clear();
    window.clear();
    tAsteroidSpawnTime -= deltaTime;
    asteroidSpawnTime -= deltaTime;

    for (size_t i = 0; i < Game::entities.size(); i++) {
        Game::entities[i]->update(deltaTime);
        Game::entities[i]->render(window);
    }
    // remove items from list; prevents memory leaks
    for (const auto& it : Game::removeList) {
        delete* it;
        Game::entities.erase(it);
    }

    // add items to list; helps prevent memory leaks
    for (auto& ptr : Game::addList) {
        Game::entities.push_back(ptr);
    }
    

    if (score <= 199) {
        levelText.setString("LEVEL 1");
        window.draw(levelText);

        // create more than 1 asteroid at a time
        if (getNumberOfSmallAsteroids() < 2 && asteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new Asteroid());
            asteroidSpawnTime = ASTEROID_SPAWN_TIME;
        }

        // create more than 1 big asteroid at a time
        if (getNumberOfLargeAsteroids() < 1 && tAsteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new tAsteroid());
            tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
        }
    }
    else if(score >= 200 && score <= 399) {
        levelText.setString("LEVEL 2");
        window.draw(levelText);

        // create more than 1 asteroid at a time
        if (getNumberOfSmallAsteroids() < 3 && asteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new Asteroid());
            asteroidSpawnTime = ASTEROID_SPAWN_TIME;
        }

        // create more than 1 big asteroid at a time
        if (getNumberOfLargeAsteroids() < 2 && tAsteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new tAsteroid());
            tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
        }
    }
    else if (score >= 400 && score <= 599) {
        levelText.setString("LEVEL 3");
        window.draw(levelText);

        // create more than 1 asteroid at a time
        if (getNumberOfSmallAsteroids() < 4 && asteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new Asteroid());
            asteroidSpawnTime = ASTEROID_SPAWN_TIME;
        }

        // create more than 1 big asteroid at a time
        if (getNumberOfLargeAsteroids() < 3 && tAsteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new tAsteroid());
            tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
        }
    }
    else if (score >= 600 && score <= 799) {
        levelText.setString("LEVEL 4");
        window.draw(levelText);

        // create more than 1 asteroid at a time
        if (getNumberOfSmallAsteroids() < 5 && asteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new Asteroid());
            asteroidSpawnTime = ASTEROID_SPAWN_TIME;
        }

        // create more than 1 big asteroid at a time
        if (getNumberOfLargeAsteroids() < 4 && tAsteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new tAsteroid());
            tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
        }
    }
    else if (score >= 800 && score <= 999) {
        levelText.setString("LEVEL 5");
        window.draw(levelText);

        // create more than 1 asteroid at a time
        if (getNumberOfSmallAsteroids() < 6 && asteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new Asteroid());
            asteroidSpawnTime = ASTEROID_SPAWN_TIME;
        }

        // create more than 1 big asteroid at a time
        if (getNumberOfLargeAsteroids() < 5 && tAsteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new tAsteroid());
            tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
        }
    }
    else if (score >= 1000 && score <= 1199) {
        levelText.setString("LEVEL 6");
        window.draw(levelText);

        // create more than 1 asteroid at a time
        if (getNumberOfSmallAsteroids() < 7 && asteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new Asteroid());
            asteroidSpawnTime = ASTEROID_SPAWN_TIME;
        }

        // create more than 1 big asteroid at a time
        if (getNumberOfLargeAsteroids() < 6 && tAsteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new tAsteroid());
            tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
        }
    }
    else if (score >= 1200 && score <= 1399) {
        levelText.setString("LEVEL 7");
        window.draw(levelText);

        // create more than 1 asteroid at a time
        if (getNumberOfSmallAsteroids() < 8 && asteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new Asteroid());
            asteroidSpawnTime = ASTEROID_SPAWN_TIME;
        }

        // create more than 1 big asteroid at a time
        if (getNumberOfLargeAsteroids() < 7 && tAsteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new tAsteroid());
            tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
        }
    }
    else if (score >= 1400 && score <= 1599) {
        levelText.setString("LEVEL 8");
        window.draw(levelText);

        // create more than 1 asteroid at a time
        if (getNumberOfSmallAsteroids() < 9 && asteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new Asteroid());
            asteroidSpawnTime = ASTEROID_SPAWN_TIME;
        }

        // create more than 1 big asteroid at a time
        if (getNumberOfLargeAsteroids() < 8 && tAsteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new tAsteroid());
            tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
        }
    }
    else if (score >= 1600 && score <= 1799) {
        levelText.setString("LEVEL 9");
        window.draw(levelText);

        // create more than 1 asteroid at a time
        if (getNumberOfSmallAsteroids() < 10 && asteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new Asteroid());
            asteroidSpawnTime = ASTEROID_SPAWN_TIME;
        }

        // create more than 1 big asteroid at a time
        if (getNumberOfLargeAsteroids() < 9 && tAsteroidSpawnTime <= 0.0f) {
            Game::entities.push_back(new tAsteroid());
            tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
        }
    }
    else {
        float newSpawn = ASTEROID_SPAWN_TIME * 4.0f;
        float newSpawn2 = tASTEROID_SPAWN_TIME * 4.0f;
        levelText.setString("LEVEL 10");
        window.draw(levelText);

        // create more than 1 asteroid at a time
        if (getNumberOfSmallAsteroids() < 12 && newSpawn <= 0.0f) {
            Game::entities.push_back(new Asteroid());
            newSpawn = ASTEROID_SPAWN_TIME;
        }

        // create more than 1 big asteroid at a time
        if (getNumberOfLargeAsteroids() < 10 && newSpawn2 <= 0.0f) {
            Game::entities.push_back(new tAsteroid());
            newSpawn2 = tASTEROID_SPAWN_TIME;
        }
    }


    scoreText.setString(std::to_string(score));
    window.draw(scoreText);

    if (state == GAME_OVER) {
        entities.clear();
        window.draw(gameOverText);
        window.draw(continueText);
        window.draw(menuText);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            begin();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            state = MENU;
        }
    }
}

void Game::gameOver() {
    if (score > highScore) {
        highScore = score;
        std::ofstream file("score.dat", std::ios::binary | std::ios::out);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(&highScore), sizeof(size_t));
            file.close();
        }
        else {
            printf("Failed to write high score to file!\n");
        }

        highScoreText.setString("High Score: " + std::to_string(highScore));
    }

    state = GAME_OVER;
}