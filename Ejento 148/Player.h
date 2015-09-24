#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
	Player(sf::Vector2f, std::string n, float s, int l);

	std::string getName();
	void setName(std::string);
	float getSpeed();
	void setSpeed(float);
	int getLives();
	void setLives(int);

	void draw(sf::RenderWindow &window);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	std::string name;
	float speed;
	int lives;
};

#endif