#include "Menu.h"
#include <iostream>
#include <string>

Menu::Menu(sf::RenderWindow& wnd)
{
	window = &wnd;
	float width = (float)window->getSize().x;
	float height = (float)window->getSize().y;
	//Load Resources
	//TODO: replace exit with throw
	if (!texture.loadFromFile("assets/bak1.png"))
	{
		exit(2);
	}
	if (!font.loadFromFile("assets/font2.ttf"))
	{
		exit(2);
	}
	size = texture.getSize();
	texture.setSmooth(false);
	texture.setRepeated(true);
	sprite.setTexture(texture);
	auto trec = sf::FloatRect(0.0, 0.0, sprite.getLocalBounds().width*2, sprite.getLocalBounds().height*2);
	sprite.setTextureRect(sf::IntRect(trec));
	sprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	sprite.setScale(0.50f, 0.50f);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Yellow);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f((width / 2) - (menu[0].getGlobalBounds().width / 2), height / (4 + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f((width / 2) - (menu[1].getGlobalBounds().width / 2), height / (4 + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Credit");
	menu[2].setPosition(sf::Vector2f((width / 2) - (menu[2].getGlobalBounds().width / 2), height / (4 + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f((width / 2) - (menu[3].getGlobalBounds().width / 2), height / (4 + 1) * 4));

	menu[4].setFont(font);
	menu[4].setFillColor(sf::Color::Yellow);
	menu[4].setString("7");
	menu[4].setPosition(sf::Vector2f((width / 2) - (menu[4].getGlobalBounds().width / 2), height / (4 + 1) * 1));

	menu[5].setFont(font);
	menu[5].setFillColor(sf::Color::White);
	menu[5].setString("1");
	menu[5].setPosition(sf::Vector2f((width / 2) - (menu[5].getGlobalBounds().width / 2), height / (4 + 1) * 2));

	menu[6].setFont(font);
	menu[6].setFillColor(sf::Color::White);
	menu[6].setString("ON");
	menu[6].setPosition(sf::Vector2f((width / 2) - (menu[6].getGlobalBounds().width / 2), height / (4 + 1) * 3));

	menu[7].setFont(font);
	menu[7].setFillColor(sf::Color::White);
	menu[7].setString("Return to main menu");
	menu[7].setPosition(sf::Vector2f((width / 2) - (menu[7].getGlobalBounds().width / 2), height / (4 + 1) * 4));

	menu[8].setFont(font);
	menu[8].setFillColor(sf::Color::White);
	menu[8].setString("Number of Colors");
	menu[8].setPosition(sf::Vector2f(((width / 2) - (menu[8].getGlobalBounds().width / 2)), (height / (4 + 1) * 1) - 30));

	menu[9].setFont(font);
	menu[9].setFillColor(sf::Color::White);
	menu[9].setString("Difficulty Level");
	menu[9].setPosition(sf::Vector2f((width / 2) - (menu[9].getGlobalBounds().width / 2), (height / (4 + 1) * 2) - 30));

	menu[10].setFont(font);
	menu[10].setFillColor(sf::Color::White);
	menu[10].setString("Sound");
	menu[10].setPosition(sf::Vector2f((width / 2) - (menu[10].getGlobalBounds().width / 2), (height / (4 + 1) * 3) - 30));


	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(int start, int end)
{
	auto tv = sprite.getPosition();
	tv.x = fmod(tv.x - 1.0, sprite.getGlobalBounds().width / 2.0);
	tv.y = fmod(tv.y - 1.0, sprite.getGlobalBounds().height / 2.0);

	sprite.setPosition(tv);

	window->clear(sf::Color::Black);

	window->draw(sprite);

	if (end == 7)
	{
		for (int i = 1; i < 4; i++)
		{
			window->draw(menu[i + end]);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		window->draw(menu[i+start]);
	}
	window->display();
}

void Menu::MoveUp(int start)
{
	if (selectedItemIndex >= 0)
	{
		menu[selectedItemIndex+ start].setFillColor(sf::Color::White);
		selectedItemIndex--;
		if (selectedItemIndex < 0)
			selectedItemIndex = 3;
		menu[selectedItemIndex+ start].setFillColor(sf::Color::Yellow);
	}
}

void Menu::MoveDown(int start)
{
	if (selectedItemIndex < 4)
	{
		menu[selectedItemIndex+start].setFillColor(sf::Color::White);
		selectedItemIndex++;
		if (selectedItemIndex >= 4)
			selectedItemIndex = 0;
		menu[selectedItemIndex+start].setFillColor(sf::Color::Yellow);
	}
}

void Menu::MoveLeft(int start, Game& g)
{
	if ((selectedItemIndex == 0 || selectedItemIndex == 1) && start == 4)
	{
		std::string k = menu[selectedItemIndex + start].getString();
		int now = std::stoi(k);
		if (now > 2)
			now--;
		menu [selectedItemIndex + start].setString(std::to_string(now));
	}
	else if (selectedItemIndex == 2 && start == 4)
	{
		std::string k = menu[selectedItemIndex + start].getString();
		if (k == "ON")
		{
			k = "OFF";
			g.music.setVolume(0.0f);
		}
		else
		{
			g.music.setVolume(30.0f);
			k = "ON";
		}
	}
}

void Menu::MoveRight(int start, Game& g)
{
	if ((selectedItemIndex == 0 || selectedItemIndex == 1) && start == 4)
	{
		std::string k = menu[selectedItemIndex + start].getString();
		int now = std::stoi(k);
		if (now < 20)
			now++;
		menu[selectedItemIndex + start].setString(std::to_string(now));
	}
	else if (selectedItemIndex == 2 && start == 4)
	{
		std::string k = menu[selectedItemIndex + start].getString();
		if (k == "ON")
		{
			k = "OFF";
			g.music.setVolume(0.0f);
		}
		else
		{
			g.music.setVolume(30.0f);
			k = "ON";
		}
		menu[selectedItemIndex + start].setString(k);
	}
}

void Menu::OptionUpdate(int& gm,Game& g)
{
	sf::Event event;
	if (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				MoveUp(4);
				break;
			case sf::Keyboard::Down:
				MoveDown(4);
				break;
			case sf::Keyboard::Left:
				MoveLeft(4, g);
				break;
			case sf::Keyboard::Right:
				MoveRight(4, g);
				break;
			case sf::Keyboard::Return:
				switch (GetPressedItem())
				{
				case 0:
				{
					std::string k = menu[4].getString();
					int now = std::stoi(k);
					g.ColorsNum = now;
					gm = 2;
					break;
				}
				case 1:
				{
					std::string k = menu[5].getString();
					int now = std::stoi(k);
					g.diff = now;
					gm = 2;
					break;
				}
				case 2:
				{
					std::cout << "Credit button has been pressed" << std::endl;
					gm = 2;
					break;
				}
				case 3:
				{
					selectedItemIndex = 1;
					gm = 1;
					break;
				}
				}
				break;
			}
			break;
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}

void Menu::Update(int& gm)
{
	sf::Event event;

	if (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				MoveUp(0);
				break;

			case sf::Keyboard::Down:
				MoveDown(0);
				break;

			case sf::Keyboard::Return:
				switch (GetPressedItem())
				{
				case 0:
				{
					std::cout << "Play button has been pressed" << std::endl;
					gm = 0;
					break;
				}
				case 1:
				{
					std::cout << "Option button has been pressed" << std::endl;
					selectedItemIndex = 0;
					gm = 2;
					break;
				}
				case 2:
				{
					std::cout << "Credit button has been pressed" << std::endl;
					gm = 3;
					break;
				}
				case 3:
				{
					gm = 4;
					window->close();
					break;
				}
				}
				break;
			}
			break;
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}
