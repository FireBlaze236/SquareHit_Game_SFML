#include "Game.h"
#include <iostream>

Game::Game(int w, int h, const char* title) 
	: GameRunning(true), gameWindow(new sf::RenderWindow(sf::VideoMode(w, h), title)), player(new Player())
{
	//Generate Random colors
	GenerateColors(73, 3);
	currentColor = 0;
	player->SetColor(colors[0]);
	player->SetPosition(sf::Vector2f(0.0f, 12.0f));
	//Set a limited framerate
	gameWindow->setFramerateLimit(60);

	//Set player status
	moving = true;
	smash = false;
	lastPosition = sf::Vector2f(0.0f, 12.0f);
	interval = 1;

	//Generate Tile Map
	GenerateTileMap(12,tileMapRows, tileMapColumns);
	tileTexture.loadFromFile("assets\\tiles.png");
	tileSprite.setTexture(tileTexture);
	
}



Game::~Game()
{
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
		}
	}

	
	//Player smashes the tiles when Space is pressed
	if (!smash && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		moving = false;
		smash = true;
		lastPosition = player->GetSprite().getPosition();
	}

	// Player Check bound
	//Get player position
	sf::Vector2f position = player->GetSprite().getPosition();
	if (position.x > 480.0f || position.x < 0.0f)
	{
		playerMoveSpeed *= -1;
	}

	//Reset position if out of bound
	if (smash && position.y > 480.0f)
	{
		smash = false;
		player->SetPosition(lastPosition);
		moving = true;
	}

	if (smash && !moving)
	{
		bool collide = false;
		sf::FloatRect playerRect = player->GetSprite().getGlobalBounds();
		for (int i = 0;i < tileMapRows && !collide; i++)
		{
			for (int j = 0; j < tileMapColumns && !collide; j++)
			{
				if (playerRect.intersects(tileRects[i][j]))
				{
					tileRects[i][j] = sf::FloatRect();
					if (tileMapArray[i][j] == currentColor)
					{
						score++;
						std::cout << "Score : " << score << " Lives:" << lives << std::endl;
					}
					else
					{
						lives--;
						std::cout << "Score : " << score << " Lives:" << lives << std::endl;
					}
					tileMapArray[i][j] = -1;
					smash = false;
					player->SetPosition(lastPosition);
					moving = true;
					collide = true;
				}
			}
		}
	}
}

void Game::Update()
{
	//Change color at intervals
	float t = intervalTimer.getElapsedTime().asSeconds();
	if (moving && t > interval)
	{
		intervalTimer.restart();
		currentColor++;
		if (currentColor >= colors.size()) currentColor = 0;
		player->SetColor(colors[currentColor]);
	}
	
	if(moving && !smash)
	{
		player->Move(sf::Vector2f(playerMoveSpeed, 0.0f));
	}

	//Detect collision with player and tile
	if (smash && !moving)
	{
		player->Move(sf::Vector2f(0.0f, playerSmashSpeed));
	}

	
	
}



void Game::Render()
{
	//Clear for render
	gameWindow->clear();
	//Area for rendering everything
	gameWindow->draw(player->GetSprite());
	DrawTileMap();
	//Display rendered output
	gameWindow->display();

}

void Game::GenerateColors(int seed, int n)
{
	srand(seed);

	for (int i = 0;i < n;i++)
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
		sf::Color c(rnr,rng,rnb,255);
		colors.push_back(c);
	}
}

void Game::GenerateTileMap(int seed, int rows, int columns)
{
	srand(seed);
	int n = colors.size(); // match colors
	for (int i = 0;i < rows;i++)
	{
		for (int j = 0;j < columns;j++)
		{
			tileMapArray[i][j] = rand() % n;
		}
	}
	
}

void Game::DrawTileMap()
{
	
	float initialx = 32.0f;
	float initialy = 200.0f;
	sf::Vector2f drawPos = sf::Vector2f(initialx, initialy);
	float spacing = 5.0f;
	for (int i = 0;i < tileMapRows; i++)
	{
		for (int j = 0; j < tileMapColumns;j++)
		{
			int idx = tileMapArray[i][j];

			//Draw single tile
			
			tileSprite.setPosition(drawPos);
			if (idx >= 0)
			{
				tileSprite.setColor(colors[idx]);
				gameWindow->draw(tileSprite);
			}

			//store rect + color for collision detect
			if (idx >= 0)
			{
				tileRects[i][j] = tileSprite.getGlobalBounds();
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



