#include "Menu.h"
#include <iostream>
#include <string>

Menu::Menu(sf::RenderWindow& wnd)
{
	window = &wnd;
	width = (float)window->getSize().x;
	height = (float)window->getSize().y;

	//Load Resources
	//TODO: replace exit with throw

	if (!texture.loadFromFile("assets/bak1.png"))
	{
		exit(2);
	}
	if (!font.loadFromFile("assets/font.ttf"))
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

	setMenu(font, sf::Color::Yellow, "Play", 1, 0, 0);
	setMenu(font, sf::Color::White, "Options", 2, 0, 1);
	setMenu(font, sf::Color::White, "Credit", 3, 0, 2);
	setMenu(font, sf::Color::White, "Exit", 4, 0, 3);
	setMenu(font, sf::Color::Yellow, "1", 1, 0, 4);
	setMenu(font, sf::Color::White, "1", 2, 0, 5);
	setMenu(font, sf::Color::White, "ON", 3, 0, 6);
	setMenu(font, sf::Color::White, "Return to main menu", 4, 0, 7);
	setMenu(font, sf::Color::White, "Number of Colors", 1, 30, 8);
	setMenu(font, sf::Color::White, "Difficulty Level", 2, 30, 9);
	setMenu(font, sf::Color::White, "Sound" , 3 , 30, 10);

	selectedItemIndex = 0;
}

void Menu::setMenu(sf::Font& f, sf::Color c, std::string s,int h, int d, int i)
{
	menu[i].setFont(f);
	menu[i].setFillColor(c);
	menu[i].setString(s);
	menu[i].setPosition(sf::Vector2f((width / 2) - (menu[i].getGlobalBounds().width / 2), (height / (4 + 1) * h) - d));
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
		if (now > 1)
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
		menu[selectedItemIndex + start].setString(k);
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
					gm = 2;
					break;
				}
				case 1:
				{	
					gm = 2;
					break;
				}
				case 2:
				{
					gm = 2;
					break;
				}
				case 3:
				{

					g.ColorsNum = std::stoi(std::string(menu[4].getString()));
					g.GenerateColors(g.ColorSeed, g.ColorsNum);
					g.ResetLevel();

					g.diff = std::stoi(std::string(menu[5].getString()));
					g.playerMoveSpeed = 5.0f;
					if (g.diff >= 2) g.playerMoveSpeed *= std::min(5, g.diff) / 2.0;
					g.ResetLevel();

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
					gm = 0;
					break;
				}
				case 1:
				{
					selectedItemIndex = 0;
					gm = 2;
					break;
				}
				case 2:
				{
					gm = 1;
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
