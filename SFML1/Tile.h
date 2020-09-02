#pragma once

#include "SFML/Graphics.hpp"

class Tile
{
public:
	sf::FloatRect rect;
	int color;
	bool isDestroyed;
	char opacity;
	float ascend;
	void Update();
	Tile();
};

