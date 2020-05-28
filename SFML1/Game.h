#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"

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

	// Tile variables
	sf::Sprite tileSprite;
	sf::Texture tileTexture;
	static const int tileMapRows = 8, tileMapColumns = 12;
	int tileCount = tileMapRows * tileMapColumns;
	sf::FloatRect tileRects[tileMapRows][tileMapColumns];
	int tileMapArray[tileMapRows][tileMapColumns];
	//UI variables

	int score = 0;
	int lives = 25;
	sf::Font font;
	sf::Text scoreText;
	sf::Text livesText;
	sf::Text timerText; // Timer to be implemented
	sf::Text pausedText;
	sf::Text gameWinText;
	sf::Text gameOverText;
	//

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
	//Ui function
	void InitUI();
	void UpdateUI();

	// Util
	void PauseGame();
	void Close();
};

