#pragma once
#include <SFML/Graphics.hpp>
class GameTile
{
public:
	bool isPassable;
	bool isExit;
	bool isCaveEntry;
	bool isCaveExit;

	sf::Vector2f pos;
	sf::Texture texture;
	sf::Sprite sprite;

	GameTile(std::string textureName, float x, float y, bool passable, bool exit);
	bool setUpSprite(std::string);
};

