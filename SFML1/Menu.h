#pragma once

#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
public:
	Menu(sf::RenderWindow& window);
	~Menu();

	void draw();
	void Update(bool& gm);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2u size;
};