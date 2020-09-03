/*
		This Project is done as Academic Project 
	for 3rd Semester Object Oriented Programming Course
*/

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "Menu.h"

int main()
{
	// Creating Game & Menu Object Simultaneouly
	Game game(512, 512, "SquareHit", 71, 1 + (rand() % 420), 1, 1);
	Menu menu(*(game.gameWindow));

	game.gameWindow->setVisible(true);
	
	// Game Loop
	while (game.IsRunning())
	{
		//MainMenu
		if (game.GameMainMenu == 1)
		{
			menu.Update(game.GameMainMenu);
			menu.draw(0, 4);
		}
		//Game Loop
		else if (game.GameMainMenu == 0) 
		{
			game.HandleEvents();
			if ((!game.GamePaused))
				game.Update();
			game.Render();
		}
		//Option Menu
		else if (game.GameMainMenu == 2)
		{
			menu.OptionUpdate(game.GameMainMenu, game);
			menu.draw(4, 7);
		}
		//Credit
		else if (game.GameMainMenu == 3)
		{
			menu.CreditShow(game.GameMainMenu);
			menu.draw(10, 14);
		}
		//Exit
		else
		{
			break;
		}
	}

	game.gameWindow->setVisible(false);

    return 0;
}
