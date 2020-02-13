#include "Player.h"



Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed): animation(texture,imageCount,switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = false;

	body.setSize(sf::Vector2f(167.0f, 110.0f));
	body.setPosition(0.0f, 0.0f);
	body.setTexture(texture);
}


Player::~Player()
{
}

void Player::Update(float deltaTime, sf::RenderWindow& window)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (body.getPosition().x >= 0)
			movement.x -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		if (body.getPosition().x <= (window.getSize().x - body.getSize().x))
			movement.x += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		if (body.getPosition().y >= 0)
			movement.y -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		if (body.getPosition().y <= (window.getSize().y - body.getSize().y))
			movement.y += speed * deltaTime;


	if (movement.x == 0.0f) {
		row = 0;
	}
	else if(abs(movement.x)> 0.0f){
		if (movement.x > 0.0f) {
			faceRight = true;
			row = 1;
		}
		else {
			faceRight = false;
			row = 1;
		}
	}
	if (movement.y == 0.0f)
		row = 0;
	else
		row = 1;

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}


