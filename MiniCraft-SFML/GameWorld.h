#pragma once
#include <SFML/Graphics.hpp>
#include "GameTile.h"
#include <vector>

class GameWorld
{
private:
	sf::Vector2i exitPos;
	sf::Vector2i playerPos;
	sf::Vector2i caveExitPos;
	std::vector<sf::Vector2i> enemyPos;
	void setUpInitialState();
	void setupEnemyPositions();
	void setUpTiles();

public:
	std::vector<std::vector<GameTile*>> tiles;
	int gridLength;
	int test;
	GameWorld();
};

