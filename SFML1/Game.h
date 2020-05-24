#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"

class Game
{

private:
	//main variables
	bool GameRunning;
	sf::RenderWindow* gameWindow;
	Player* player;
	//Colors
	std::vector<sf::Color> colors;
	int currentColor;
	float interval;
	//
	sf::Clock gameTimer;
	sf::Clock intervalTimer;
	//player variables
	float playerMoveSpeed = 5.0f;
	float playerSmashSpeed = 10.0f;
	sf::Vector2f lastPosition;
	bool moving;
	bool smash;

	// Tile variables
	sf::Sprite tileSprite;
	sf::Texture tileTexture;
	static const int tileMapRows = 8, tileMapColumns = 12;
	sf::FloatRect tileRects[tileMapRows][tileMapColumns];
	int tileMapArray[tileMapRows][tileMapColumns];
	//UI variables

	int score = 0;
	int lives = 10;
public:
	Game() = delete;
	Game(int w, int h,const char* title);
	~Game();

	bool IsRunning() const { return gameWindow->isOpen() && GameRunning; }

	// Essential methods
	void HandleEvents();
	void Update();
	void Render();
	void GenerateColors(int seed, int n);
	void GenerateTileMap(int seed, int rows, int columns);
	void DrawTileMap();
};

