#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Enemy();
	void Update(float deltaTime, sf::RenderWindow& window, Player player);
	void Draw(sf::RenderWindow& window);
	sf::RectangleShape body;
	void setSpeed(float speed);
	float getSpeed();
private:
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
};

