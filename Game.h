#pragma once
#include <vector>
#include <list>
#include "Entity.h"
#include <unordered_map>
#include <SFML/Audio.hpp>

class Game
{
public:
	static void init();
	static void begin();
	static void update(sf::RenderWindow& window, float deltaTime);
	static void gameOver();

	static std::vector<Entity*> entities;
	static std::list <std::vector<Entity*>::const_iterator> removeList;
	static std::list <Entity*> addList;

	static size_t score;

	static sf::SoundBuffer shootSoundBuffer;
	static sf::SoundBuffer largeShootSoundBuffer;
	static sf::Sound shootSound;
	static sf::Sound largeShootSound;

private:
	static float asteroidSpawnTime;
	static float tAsteroidSpawnTime;
	static size_t highScore;

	static sf::Text scoreText;
	static sf::Font font;

	static sf::Text gameOverText;
	static sf::Text continueText;

	static sf::Text highScoreText;
	static sf::Text titleText;
	static sf::Text menuText;
	static sf::Text playText;
	static sf::Text levelText;
	static sf::Text lastLevelText;
	static sf::Text quitText;

	static enum State { MENU, PLAYING, GAME_OVER } state;
};

