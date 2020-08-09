#include "Menu.h"


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("FredokaOne.ttf"))
	{
		exit(2);
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Yellow);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f((width / 2) - 30, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f((width / 2) - 50, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Credit");
	menu[2].setPosition(sf::Vector2f((width / 2) - 45, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f((width / 2) - 30, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		if (selectedItemIndex < 0)
			selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
		menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		if (selectedItemIndex >= MAX_NUMBER_OF_ITEMS)
			selectedItemIndex = 0;
		menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
	}
}
