#include "Enemy.h"



Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) : animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = false;

	body.setSize(sf::Vector2f(101.5f, 120.5f));
	body.setPosition(500.0f, 500.0f);
	body.setTexture(texture);
}


Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime, sf::RenderWindow & window, Player player)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if(player.body.getPosition().x < this->body.getPosition().x)
		movement.x -= speed * deltaTime;
	if (player.body.getPosition().x > this->body.getPosition().x)
		movement.x += speed * deltaTime;
	if (player.body.getPosition().y < this->body.getPosition().y)
		movement.y -= speed * deltaTime;
	if (player.body.getPosition().y > this->body.getPosition().y)
		movement.y += speed * deltaTime;

	if (movement.x == 0.0f) {
		row = 0;
	}
	else {
		row = 1;
		if (movement.x > 0.0f)
			faceRight = false;
		else
			faceRight = true;
	}
	if (movement.y == 0.0f)
		row = 0;
	else
		row = 1;
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Enemy::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void Enemy::setSpeed(float speed)
{
	this->speed = speed;
}

float Enemy::getSpeed()
{
	return this->speed;
}
