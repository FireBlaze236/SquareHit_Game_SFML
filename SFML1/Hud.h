#pragma once

#include <SFML/Graphics.hpp>

class Hud
{
	sf::Font& font;
	sf::Text scoreText;
	sf::Text livesText;
	sf::Text timerText; // Timer to be implemented
	sf::Text pausedText;
	sf::Text gameWinText;
	sf::Text gameOverText;
public:
	void Draw(sf::RenderWindow* render);
	void Update(int score, int lives);

	Hud() = delete;
	Hud(sf::Font& f);
};

