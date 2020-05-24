#pragma once
#include "SFML/Graphics.hpp"
class Player
{
private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
public:
	Player();
	~Player();

	const sf::Sprite& GetSprite() { return playerSprite; }


	void SetPosition(const sf::Vector2f& pos);
	void Move(const sf::Vector2f& dir);
	void SetColor(sf::Color& color);
};

