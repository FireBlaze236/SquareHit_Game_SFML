#include "Hud.h"
#include <sstream>

Hud::Hud(sf::Font& f) : font(f)
{
	scoreText.setFont(font);
	livesText.setFont(font);
	timerText.setFont(font);

	scoreText.setCharacterSize(24);
	livesText.setCharacterSize(24);
	timerText.setCharacterSize(24);

	scoreText.setPosition(sf::Vector2f(0.0f, 0.0f));
	livesText.setPosition(sf::Vector2f(400.0f, 0.0f));
	//
	//Find a way to center it according to window
	pausedText.setFont(font);
	pausedText.setCharacterSize(48);
	pausedText.setString("Paused");
	pausedText.setPosition(140, 100);

	// Game win

	gameWinText.setFont(font);
	gameWinText.setCharacterSize(48);
	gameWinText.setString("Congratulations !");
	gameWinText.setPosition(20, 100);

	// Game over
	gameOverText.setFont(font);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setCharacterSize(48);
	gameOverText.setString("Game Over!");
	gameOverText.setPosition(140, 100);
}

void Hud::Update(int score, int lives, int state)
{
	std::stringstream ss;
	ss << "Score:" << score;
	std::string scoreString;
	ss >> scoreString;
	scoreText.setString(scoreString);

	ss.clear();

	ss << "Lives:" << lives;
	std::string livesString;
	ss >> livesString;
	livesText.setString(livesString);

	_gstate = state;
}

void Hud::Draw(sf::RenderWindow* render)
{
	render->draw(scoreText);
	render->draw(livesText);
	switch (_gstate) {
	case 0:
		render->draw(pausedText);
		break;
	case 1:
		render->draw(gameWinText);
		break;
	case 2:
		render->draw(gameOverText);
		break;
	default:
		break;
	}
}
