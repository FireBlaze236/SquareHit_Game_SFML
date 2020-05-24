#include "Game.h"



Game::Game(int w, int h, const char* title) 
	: GameRunning(true), gameWindow(new sf::RenderWindow(sf::VideoMode(w, h), title)), player(new Player())
{
	//Generate Random colors
	GenerateColors(12, 3);
	currentColor = 0;
	player->SetPosition(sf::Vector2f(0.0f, 12.0f));
	//Set a limited framerate
	gameWindow->setFramerateLimit(60);
	moving = true;
	smash = false;
	lastPosition = sf::Vector2f(0.0f, 12.0f);
	interval = 1;
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


	
}

void Game::Update()
{
	//Change color at intervals
	float t = intervalTimer.getElapsedTime().asSeconds();
	if (moving && t > interval)
	{
		intervalTimer.restart();
		srand(time(NULL));
		currentColor = rand() % colors.size();
		player->SetColor(colors[currentColor]);
	}
	if(moving && !smash)
	{
		player->Move(sf::Vector2f(playerMoveSpeed, 0.0f));
	}

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
	//Display rendered output
	gameWindow->display();

}

void Game::GenerateColors(int seed, int n)
{
	srand(seed);

	for (int i = 0;i < n;i++)
	{
		int rnr = 150 + (rand() % 105);
		int rng = 150 + (rand() % 105);
		int rnb = 150 + (rand() % 105);
		sf::Color c(rnr,rng,rnb,255);
		colors.push_back(c);
	}
}

