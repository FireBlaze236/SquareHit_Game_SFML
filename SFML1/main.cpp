#include "Game.h"

int main()
{
	Game game(512, 512, "SquareHit");
	while (game.IsRunning())
	{
		game.HandleEvents();
		game.Update();
		game.Render();
	}
    return 0;
}