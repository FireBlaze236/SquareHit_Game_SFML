#include "Tile.h"

void Tile::Update()
{
	if (isDestroyed)
	{
		if (opacity > 0)
			opacity -= 15;
		ascend += 1.0f;
	}
}

Tile::Tile():color(0) {
	isDestroyed = false;
	opacity = 255;
	ascend = 0.0f;
}