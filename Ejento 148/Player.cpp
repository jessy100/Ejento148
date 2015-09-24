// file Player.cpp

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>
#include <iostream>

Player::Player(sf::Vector2f pos, std::string n, float s, int l) : 
	position(pos), name(n), speed(s), lives(l)
{
	if (!texture.loadFromFile("resources/images/ninja.jpg")) {
		// error...
		std::cout << "Could not load ninja sprite";
	}

	sprite.setTexture(texture);
	sprite.setPosition(position);
}

std::string Player::getName() { return name; }
void Player::setName(std::string s) { name = s; }
float Player::getSpeed() { return speed; }
void Player::setSpeed(float s) { speed = s; }
int Player::getLives() { return lives; }
void Player::setLives(int l) { lives = l; }

void Player::draw(sf::RenderWindow &window) {
	// Draw a circle
	window.draw(sprite);
}
