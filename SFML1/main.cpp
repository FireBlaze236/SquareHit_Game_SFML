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

	ms = 1;
	cs = 9;
	cn = 7;
	d = 5;

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

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Test 32");

	sf::Texture texture;
	if (!texture.loadFromFile("Bak.png"))
	{
		return 1;
	}

	sf::Sprite sprite;
	sf::Vector2u size = texture.getSize();
	sprite.setTexture(texture);

	Menu menu((float)window.getSize().x, (float)window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
					{
						std::cout << "Play button has been pressed" << std::endl;

						Game game(512, 512, "SquareHit", ms, cn, cs, d);

						game.gameWindow->setVisible(true);
						// Game Loop
						while (game.IsRunning())
						{
							game.HandleEvents();
							if (!game.GamePaused)
								game.Update();
							game.Render();
						}

						game.gameWindow->setVisible(false);
						
						break;
					}
					case 1:
						std::cout << "Option button has been pressed" << std::endl;
						break;
					case 2:
						std::cout << "Credit button has been pressed" << std::endl;
						break;
					case 3:
						window.close();
						break;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		window.clear(sf::Color::Black);

		window.draw(sprite);

		menu.draw(window);

		window.display();
	}

    return 0;
}