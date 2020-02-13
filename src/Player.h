#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();
	void Update(float deltaTime, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	sf::RectangleShape body;
	
private:
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
};

