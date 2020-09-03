#pragma once

#include "SFML/Graphics.hpp"

class Tile
{
public:
	sf::FloatRect rect;
	int color;
	bool isDestroyed;
	int opacity;
	float ascend;
	void Update();
	Tile();
};

