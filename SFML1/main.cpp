#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "Menu.h"

int main()
{
	//Placeholder UI
	/*std::cout << "Welcome to Square Hit! Press any key to continue..." <<std::endl;
	std::cin.get();*/
	int ms,cs,cn,d;

	ms = 71;
	cs = 1 + (rand()%420);
	cn = 1;
	d = 1;

	/*std::cout << "Enter Map Seed : ";
	std::cin >> ms;
	
	std::cout << "Enter number of colors (default 3, max 10): ";
	std::cin >> cn;

	std::cout << "Enter Color Generate Seed : ";
	std::cin >> cs;
	
	
	std::cout << "Enter Difficulty multiplier (default 1, max 5): ";
	std::cin >> d;*/

	//std::cout << "Game loaded!" << std::endl;
	//std::cout << "Enjoy!";

	//sf::RenderWindow window(sf::VideoMode(512, 512), "Test 32");

	Game game(512, 512, "SquareHit", ms, cn, cs, d);
	Menu menu(*(game.gameWindow));

	game.gameWindow->setVisible(true);
	// Game Loop
	while (game.IsRunning())
	{
		
		if (game.GameMainMenu == 1)
		{
			menu.Update(game.GameMainMenu);
			menu.draw(0, 4);
		}
		else if (game.GameMainMenu == 0) 
		{
			game.HandleEvents();
			if ((!game.GamePaused))
				game.Update();
			game.Render();
		}
		else if (game.GameMainMenu == 2)
		{
			menu.OptionUpdate(game.GameMainMenu, game);
			menu.draw(4, 7);
		}
		else
		{
			break;
		}
	}

	game.gameWindow->setVisible(false);

	/*

		//window.clear(sf::Color::Black);

		//window.draw(sprite);

		menu.draw(window);

		window.display();
	}
	*/

    return 0;
}