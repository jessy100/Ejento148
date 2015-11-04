#ifndef _BULLET_HPP
#define _BULLET_HPP

#include <SFML/Graphics.hpp>
#include "Player.h"

class Bullet {
public:
	Bullet(sf::Vector2f, std::string);
	
	bool hasHit() { return impact; }
	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
	void CheckCollision(Player &);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::IntRect bulletRect;

	int bulletHeight = 10,
		bulletWidth = 10, 
		bulletSpeed = 2;

	bool impact = false;
	std::string direction;
};

#endif