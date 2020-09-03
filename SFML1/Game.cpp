#include "Game.h"
#include <iostream>
#include <string>
#include <functional>

Game::Game(int w, int h, const char* title, int ms, int cn, int cs, int d) : 
	MapSeed(ms),
	ColorsNum(cn), 
	ColorSeed(cs), 
	diff(d), 
	GameRunning(true), 
	gameWindow(new sf::RenderWindow(sf::VideoMode(w, h), title)), 
	player(new Player()),
	hud(font)
{
	 
	//TODO: use better flags
	GamePaused = false;
	GameMainMenu = 1;

	//Generate Random colors
	GenerateColors(ColorSeed, std::min(10, ColorsNum));
	currentColor = 0;
	player->SetColor(colors[0]);
	player->SetPosition(sf::Vector2f(0.0f, 12.0f));
	//Set a limited framerate
	gameWindow->setFramerateLimit(60);

	//Set player status
	moving = true;
	smash = false;
	outOfBounds = false;
	lastPosition = sf::Vector2f(0.0f, 12.0f);
	interval = 1;
	if (diff >= 2) playerMoveSpeed *= std::min(5, diff) / 2;
	//Generate Tile Map
	GenerateTileMap(MapSeed, tileMapRows, tileMapColumns);
	tileTexture.loadFromFile("assets/tiles.png");
	tileSprite.setTexture(tileTexture);
	
	//Init UI
	font.loadFromFile("assets/font.ttf");

	//Init Audio
	musicBuff.loadFromFile("assets/music.wav");
	music.setBuffer(musicBuff);
	//music.setVolume(0.0f);
	music.setLoop(true);
	music.play();
	colSoundBuf.loadFromFile("assets/col.wav");
	colSound.setBuffer(colSoundBuf);
	spaceSoundBuf.loadFromFile("assets/space.wav");
	spaceSound.setBuffer(spaceSoundBuf);
}



Game::~Game()
{
	music.stop();
	delete gameWindow;
	delete player;
}

void Game::HandleEvents()
{
	// poll events only when window is open
	sf::Event e;
	while (gameWindow->pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
		{
			gameWindow->close();
			break;
		}
		case sf::Event::KeyReleased:
		{
			if (e.key.code == sf::Keyboard::Escape)
			{
				GamePaused = !GamePaused;
			}
			if (e.key.code == sf::Keyboard::Q && GamePaused)
			{
				GotoMenu();
			}
		}
		}

		if ((GameWin || GameOver) && e.type == sf::Event::KeyReleased && (e.key.code == sf::Keyboard::Escape || e.key.code == sf::Keyboard::Q))
		{
			//Close();
			GotoMenu();
			ResetLevel();
		}
	}
	// Game HUD (Texts)
	int gstate = -1;
	if (GamePaused && !(GameWin || GameOver || GameMainMenu!=0))
		gstate = 0;
	else if (GameWin)
		gstate = 1;
	else if (GameOver)
		gstate = 2;
	hud.Update(score, lives, gstate);
}



void Game::Update()
{
	for (int i = 0; i < tileMapRows; i++)
	{
		for (int j = 0; j < tileMapColumns; j++)
		{
			tiles[i][j].Update();
		}
	}
	//Change color at intervals
	float t = intervalTimer.getElapsedTime().asSeconds();
	if (moving && t > interval)
	{
		intervalTimer.restart();
		currentColor++;
		if (currentColor >= (int)colors.size()) currentColor = 0;
		player->SetColor(colors[currentColor]);
	}
	
	if(moving && !smash)
	{
		player->Move(sf::Vector2f(playerMoveSpeed, 0.0f));
	}

	//Detect collision with player and tile
	if (smash && !moving)
	{
		intervalTimer.restart();
		float u = 0.1f; //playerSmashSpeed;
		float s = abs(player->GetSprite().getPosition().y - lastPosition.y);
		float a = 2.0f;
		float v = std::sqrt(u * u + 2 * a * s);
		player->Move(sf::Vector2f(0.0f, v));
	}

	if (lives == 0)
	{
		PauseGame();
		GameOver = true;
	}
	else if (tileCount == 0)
	{
		PauseGame();
		GameWin = true;
	}
	// Player smashes the tiles when Space is pressed
	if (!smash && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		moving = false;
		smash = true;
		lastPosition = player->GetSprite().getPosition();
		spaceSound.play();
	}

	// Switch direction when player hits edge of screen
	sf::Vector2f position = player->GetSprite().getPosition();
	if (position.x > 480.0f || position.x < 0.0f)
	{
		if (!outOfBounds)
		{
			playerMoveSpeed *= -1;
			outOfBounds = true;
		}
	}
	if (outOfBounds)
	{
		if (position.x <= 485.0f && position.y >= -5.0f)
		{
			outOfBounds = false;
		}
	}

	// Handle end of smash action when player falls through screen
	if (smash && position.y > 480.0f)
	{
		smash = false;
		player->SetPosition(lastPosition);
		moving = true;
	}

	// handle end of smash when player hits a block
	if (smash && !moving)
	{
		bool collide = false;
		sf::FloatRect playerRect = player->GetSprite().getGlobalBounds();
		for (int i = 0; i < tileMapRows && !collide; i++)
		{
			for (int j = 0; j < tileMapColumns && !collide; j++)
			{
				// NOTE: this section probably needs cleaning up
				auto destroyTile = [&](int x, int y)
				{
					//tiles[x][y].rect = sf::FloatRect();
					tiles[x][y].isDestroyed = true;
					//tileMapArray[x][y] = -1;
					tileCount--;
				};

				if (playerRect.intersects(tiles[i][j].rect) && !tiles[i][j].isDestroyed)
				{
					if (tiles[i][j].color == currentColor)
					{
						// NOTE: I'm not sure whether using lambdas in this manner is good or not -sp
						std::function<void(int, int)> floodFill = [&](int x, int y)
						{
							if (x < tileMapRows && y < tileMapColumns && x >= 0 && y >= 0) {
								if (tiles[x][y].color == currentColor && !tiles[x][y].isDestroyed) {
									destroyTile(x, y);
									score++;
									floodFill(x + 1, y);
									floodFill(x - 1, y);
									floodFill(x, y - 1);
									floodFill(x, y + 1);
								}
							}
						};
						floodFill(i, j);
					}
					else
					{
						lives--;
						destroyTile(i, j);
					}

					smash = false;
					player->SetPosition(lastPosition);
					moving = true;
					collide = true;
					colSound.play();
				}
			}
		}
	}
}


void Game::GenerateColors(int seed, int n)
{
	colors.clear();
	srand(seed);

	for (int i = 0; i < n; i++)
	{
		int rnr = 100 + (rand() % 100);
		int rng = 100 + (rand() % 100);
		int rnb = 100 + (rand() % 100);
		if (i % 2 == 0)
			rnr += 55;
		else if (i % 3 == 0)
			rng += 55;
		else
			rnb += 55;
		sf::Color c(rnr, rng, rnb, 255);
		colors.push_back(c);
	}
}

void Game::GenerateTileMap(int seed, int rows, int columns)
{
	srand(seed);
	int n = colors.size(); // match colors
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			tiles[i][j].color = rand() % n;
		}
	}
}


void Game::DrawTileMap()
{
	float initialx = 32.0f;
	float initialy = 200.0f;
	sf::Vector2f drawPos = sf::Vector2f(initialx, initialy);
	float spacing = 5.0f;
	for (int i = 0; i < tileMapRows; i++)
	{
		for (int j = 0; j < tileMapColumns; j++)
		{
			int idx = tiles[i][j].color;
			int opc = tiles[i][j].opacity;

			//Draw single tile

			sf::Color col = colors[idx];
			sf::Vector2f pos = drawPos;

			//if (!tiles[i][j].isDestroyed)
			//	gameWindow->draw(tileSprite);
			if (tiles[i][j].isDestroyed) {
				col.a = opc >= 0 ? opc : 0;
				pos.y -= tiles[i][j].ascend;
			}
			tileSprite.setPosition(pos);
			tileSprite.setColor(col);
			gameWindow->draw(tileSprite);

			//store rect + color for collision detect
			if (idx >= 0)
			{
				tiles[i][j].rect = tileSprite.getGlobalBounds();
			}
			//advance column
			drawPos.x += 32 + spacing;
		}

		//reset to left
		drawPos.x = initialx;
		//advance row
		drawPos.y += 32 + spacing;
	}

}


void Game::Render()
{
	//Clear for render
	gameWindow->clear();
	//Area for rendering everything
	//UI
	hud.Draw(gameWindow);
	gameWindow->draw(player->GetSprite());
	DrawTileMap();
	//Display rendered output
	gameWindow->display();

}

void Game::PauseGame()
{
	GamePaused = true;
}

void Game::GotoMenu()
{
	GameMainMenu = 1;
}

void Game::Close()
{
	GameRunning = false;
}

void Game::ResetLevel()
{
	GamePaused = false;
	GameOver = false;
	GameWin = false;
	player->SetPosition(sf::Vector2f(0.0f, 12.0f));
	score = 0;
	lives = 25;
	static const int tileMapRows = 8, tileMapColumns = 12;
	GenerateTileMap(MapSeed, tileMapRows, tileMapColumns);
	for (int i = 0; i < tileMapRows; i++) {
		for (int j = 0; j < tileMapColumns; j++) {
			tiles[i][j].isDestroyed = false;
		}
	}
	tileCount = tileMapRows * tileMapColumns;
}
