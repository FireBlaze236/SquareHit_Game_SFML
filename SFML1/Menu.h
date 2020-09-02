#pragma once

#include "SFML/Graphics.hpp"
#include "Game.h"

#define MAX_NUMBER_OF_ITEMS 11

class Menu
{
public:
	Menu(sf::RenderWindow& window);
	~Menu();

	void draw(int, int);
	void Update(int& gm);
	void OptionUpdate(int& gm, Game& g);
	//void CreditShow(int& gm);
	void MoveUp(int);
	void MoveDown(int);
	void MoveLeft(int start, Game& g);
	void MoveRight(int start, Game& g);
	int GetPressedItem() { return selectedItemIndex; }
	int selectedItemIndex;
private:
	
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2u size;
};