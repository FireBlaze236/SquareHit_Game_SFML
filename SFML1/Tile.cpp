#include "Tile.h"

void Tile::Update()
{
	if (isDestroyed)
	{
		if (!opacity)
			opacity--;
		ascend += 1.0f;
	}
}

Tile::Tile() {
	isDestroyed = false;
	opacity = 255;
	ascend = 0.0f;
}