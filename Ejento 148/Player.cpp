// file Player.cpp

#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player(std::string n, float s, int l) : 
	name(n), speed(s), lives(l) {
}

std::string Player::getName() { return name; }
void Player::setName(std::string s) { name = s; }
float Player::getSpeed() { return speed; }
void Player::setSpeed(float s) { speed = s; }
int Player::getLives() { return lives; }
void Player::setLives(int l) { lives = l; }

void Player::draw(sf::RenderWindow & window) {
	// Draw a circle
	window.draw();
}
