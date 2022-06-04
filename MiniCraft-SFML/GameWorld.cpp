#include "GameWorld.h"
#include "GamePlay.h"
#include <iostream>

GameWorld::GameWorld()
{
	gridLength = 1; //8
	setUpInitialState();
}

void GameWorld::setUpInitialState()
{
	exitPos = sf::Vector2i(1, 0);
	playerPos = sf::Vector2i(gridLength - 1, gridLength - 1);
	setupEnemyPositions();
	setUpTiles();
	//GamePlay::makeWorld();
}

void GameWorld::setupEnemyPositions()
{
	/*enemyPos.clear();
	enemyPos.push_back(sf::Vector2i(0, 2));
	enemyPos.push_back(sf::Vector2i(6, 0));
	enemyPos.push_back(sf::Vector2i(2, 7));*/

}

void GameWorld::setUpTiles()
{
	tiles.clear();
}