#include "Hud.h"
#include <sstream>

Hud::Hud(sf::Font& f) : font(f), _gstate(-1) { }

void Hud::Init(double x, double y) {
	scoreText.setFont(font);
	livesText.setFont(font);
	timerText.setFont(font);

	scoreText.setCharacterSize(24);
	livesText.setCharacterSize(24);
	timerText.setCharacterSize(24);

	scoreText.setPosition(sf::Vector2f(0.0f, 0.0f));
	livesText.setPosition(sf::Vector2f(400.0f, 0.0f));

	//Find a way to center it according to window
	pausedText.setFont(font);
	pausedText.setCharacterSize(48);
	pausedText.setString("Paused");
	pausedText.setPosition((x / 2) - (pausedText.getGlobalBounds().width / 2), y / 4);

	// Game win
	gameWinText.setFont(font);
	gameWinText.setCharacterSize(48);
	gameWinText.setString("Congratulations !");
	gameWinText.setPosition((x / 2) - (gameWinText.getGlobalBounds().width / 2), y / 4);

	// Game over
	gameOverText.setFont(font);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setCharacterSize(48);
	gameOverText.setString("Game Over!");
	gameOverText.setPosition((x / 2) - (gameOverText.getGlobalBounds().width / 2), y / 4);

	/*
	// Transparent Pause Background
	_pauseBkg.loadFromFile("assets/clr.png");
	pauseBkg.setTexture(_pauseBkg);
	auto txc = pauseBkg.getColor();
	txc.a = 128;
	pauseBkg.setColor(txc);
	pauseBkg.setOrigin(0, 0);
	// draw across entire screen
	pauseBkg.setScale(x / pauseBkg.getLocalBounds().width, y / pauseBkg.getLocalBounds().height);
	*/
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
	switch (_gstate){
	case 0:
		//render->draw(pauseBkg);
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
