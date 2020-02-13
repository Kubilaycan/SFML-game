#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include <string>
#include <sstream>
#include <fstream>


sf::Vector2f foodRandom(sf::Vector2f a, sf::RenderWindow& window);

int main(){
	//Window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Asi Kertenkele", sf::Style::Close | sf::Style::Resize);
	sf::RectangleShape background;
	sf::Texture bckgrndTexture;
	bckgrndTexture.loadFromFile("background.png");
	background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	background.setTexture(&bckgrndTexture);
	//Player/Enemy Texture
	sf::Texture playerTexture;
	playerTexture.loadFromFile("playerSprite.png");
	sf::Texture enemyTexture;
	enemyTexture.loadFromFile("enemy.png");
	Player player(&playerTexture, sf::Vector2u(4, 2), 0.5f, 500.0f);
	Enemy enemy(&enemyTexture, sf::Vector2u(4, 2), 0.3f, 50.0f);
	sf::Texture playerTexture2;
	playerTexture2.loadFromFile("enemy1.png");
	//Delta time
	float deltaTime = 0.0f;
	sf::Clock clock;

	//Sound
	sf::SoundBuffer buffer, buffer1;
	buffer.loadFromFile("sound.wav");
	buffer1.loadFromFile("sound1.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();

	/*------------------------------FOOD---------------------------------*/
	sf::RectangleShape food;
	food.setSize(sf::Vector2f(100.0f, 100.0f));
	sf::Texture foodtexture;
	foodtexture.loadFromFile("food.png");
	food.setTexture(&foodtexture);
	sf::Vector2f foodposition;
	foodposition = foodRandom(foodposition, window);
	food.setPosition(foodposition);


	

	/*-------------------------------------------------------------------*/
	


	//score to screen
	sf::Text text;
	sf::Font font;
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Red);
	text.setPosition(sf::Vector2f(160.0f, 590.0f));
	text.setString("0");

	//game over
	//sf::Text gameover;
	//gameover.setFont(font);
	//gameover.setString("GAME OVER");
	//gameover.setCharacterSize(500);
	//gameover.setOrigin(25.0f, 250.0f);
	//gameover.setFillColor(sf::Color::Red);
	//gameover.setPosition(window.getSize().x, window.getSize().y);


	//Score-highest score
	sf::Text sscore;
	sf::Text highestscore;
	sscore.setFont(font);
	highestscore.setFont(font);
	sscore.setCharacterSize(50);
	highestscore.setCharacterSize(50);
	sscore.setFillColor(sf::Color::Red);
	highestscore.setFillColor(sf::Color::Red);
	sscore.setPosition(sf::Vector2f(10.0f, 590.0f));
	highestscore.setPosition(sf::Vector2f(10.0f, 650.0f));
	sscore.setString("Score: ");
	highestscore.setString("Highest Score: ");

	sf::Text hscorenum;
	hscorenum.setFont(font);
	hscorenum.setCharacterSize(50);
	hscorenum.setFillColor(sf::Color::Red);
	hscorenum.setPosition(sf::Vector2f(340.0f, 650.0f));





	char hscore;
	std::ifstream hscorefile;
	hscorefile.open("score.dat", std::ios::in | std::ios::binary);
	hscorefile.read((char*)&hscore, sizeof(hscore));
	hscorefile.close();
	
	std::stringstream hs;
	hs << int(hscore);
	hscorenum.setString(hs.str());
	//--------------------------


	int score = 0;
	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
				case sf::Event::Closed:
					sound.stop();
					window.close();
					break;
			}
		}

		if (player.body.getGlobalBounds().intersects(food.getGlobalBounds())) {
			foodposition = foodRandom(foodposition, window);
			food.setPosition(foodposition);
			score++;
			int *tempscore = new int(score);
			std::stringstream ss;
			ss << *tempscore;
			text.setString(ss.str());
			delete tempscore;
			enemy.setSpeed(enemy.getSpeed() + 2.0f);
			float enemyNewX = enemy.body.getSize().x*1.02f;
			float enemyNewy = enemy.body.getSize().y*1.02f;
			enemy.body.setSize(sf::Vector2f(enemyNewX, enemyNewy));
			if (int(score) == 10) {
				sound.stop();
				sound.setBuffer(buffer1);
				sound.play();
				enemy.body.setTexture(&playerTexture2);
				//enemy.body.setSize(sf::Vector2f(152.25f, 180.75f));
			}
		}



		if (player.body.getGlobalBounds().intersects(enemy.body.getGlobalBounds())) {
			if (score > hscore) {
				std::ofstream scorefile;
				scorefile.open("score.dat", std::ios::out | std::ios::binary);
				scorefile.write((char*)&score, sizeof(score));
				scorefile.close();
			}
			
			
			
			window.close();
		}



		player.Update(deltaTime, window);
		enemy.Update(deltaTime, window, player);
		window.clear(sf::Color::White);
		window.draw(background);
		player.Draw(window);
		enemy.Draw(window);
		window.draw(food);
		window.draw(text);
		window.draw(sscore);
		window.draw(highestscore);
		window.draw(hscorenum);
		window.display();
	}
	//game over
	//window.clear(sf::Color::White);
	//window.draw(background);
	//window.draw(gameover);
	//window.display();
	//window.clear(sf::Color::White);
	//window.draw(gameover);
	//window.display();
	//while (shutgame.asSeconds() < 0.3f) {
	//}
	
	return 0;

}



sf::Vector2f foodRandom(sf::Vector2f a, sf::RenderWindow& window) {
	a.x = float(rand() % window.getSize().x);
	a.y = float(rand() % window.getSize().y);
	while (a.y > 490.0f)
		a.y = float(rand() % window.getSize().y);
	a.x -= 50.0f;
	a.y -= 50.0f;
	return a;
}
