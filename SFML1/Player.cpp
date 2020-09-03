#include "Player.h"



Player::Player()
{
	playerTexture.loadFromFile("assets/player.png");
	playerSprite.setTexture(playerTexture);
}


Player::~Player()
{
}

void Player::Move(const sf::Vector2f& dir)
{
	playerSprite.move(dir);
}

void Player::SetColor(sf::Color& color)
{
	playerSprite.setColor(color);
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	playerSprite.setPosition(pos);
}

