#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "Hud.h"
#include "Tile.h"
#include "Level.h"

class Game
{
public:
	int MapSeed = 12;
	int ColorsNum = 3;
	int ColorSeed = 73;
	int diff = 1;
	sf::RenderWindow* gameWindow;
	bool GamePaused;
private:
	//main variables
	bool GameRunning;
	
	bool GameWin;
	bool GameOver;
	//sf::RenderWindow* gameWindow;
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
	bool outOfBounds;

	// Tile variables
	sf::Sprite tileSprite;
	sf::Texture tileTexture;
	static const int tileMapRows = 8, tileMapColumns = 12;
	int tileCount = tileMapRows * tileMapColumns;
	Tile tiles[tileMapRows][tileMapColumns];
	//sf::FloatRect tileRects[tileMapRows][tileMapColumns];
	//int tileMapArray[tileMapRows][tileMapColumns];

	int score = 0;
	int lives = 25;
	sf::Font font;
	Hud hud;

	//Audio
	sf::SoundBuffer musicBuff;
	sf::Sound music;
	sf::SoundBuffer colSoundBuf, spaceSoundBuf;
	sf::Sound spaceSound, colSound;
public:
	Game() = delete;
	Game(int w, int h, const char* title, int ms, int cn, int cs, int d);
	~Game();

	bool IsRunning() const { return gameWindow->isOpen() && GameRunning; }

	// Essential methods
	void HandleEvents();
	void Update();
	void Render();
	void GenerateColors(int seed, int n);
	void GenerateTileMap(int seed, int rows, int columns);
	void DrawTileMap();

	// Util
	void PauseGame();
	void Close();
};

