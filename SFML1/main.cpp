#include "Game.h"
#include <iostream>
int main()
{
	//Placeholder UI
	std::cout << "Welcome to Square Hit! Press any key to continue..." <<std::endl;
	std::cin.get();
	int ms,cs,cn,d;
	std::cout << "Enter Map Seed : ";
	std::cin >> ms;
	
	std::cout << "Enter number of colors (default 3, max 10): ";
	std::cin >> cn;

	std::cout << "Enter Color Generate Seed : ";
	std::cin >> cs;
	
	
	std::cout << "Enter Difficulty multiplier (default 1, max 5): ";
	std::cin >> d;

	Game game(512, 512, "SquareHit",ms,cn,cs,d);
	game.gameWindow->setVisible(false);
	std::cout << "Game loaded!" << std::endl;
	std::cout << "Enjoy!";

	//End UI
	game.gameWindow->setVisible(true);
	// Game Loop
	while (game.IsRunning())
	{
		game.HandleEvents();
		game.Update();
		game.Render();
	}
    return 0;
}