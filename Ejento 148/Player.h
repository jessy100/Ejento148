#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "AnimatedSprite.h"

class Player {
public:
	Player(sf::Vector2f, std::string n, float s, int l);

	std::string Player::getName() { return name; }
	void Player::setName(std::string s) { name = s; }
	float Player::getSpeed() { return speed; }
	void Player::setSpeed(float s) { speed = s; }
	int Player::getLives() { return lives; }
	void Player::setLives(int l) { lives = l; }
	void Player::setAnimation(Animation &animation) { currentAnimation = &animation; }

	bool CheckCollision(sf::IntRect collider);
	
	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position, movement;
	sf::IntRect playerRect;
	std::string name;
	float speed;
	int lives, playerHeight = 32, playerWidth = 32;
	Animation *currentAnimation, walkingAnimationDown, walkingAnimationLeft;
	Animation walkingAnimationRight, walkingAnimationUp;
	AnimatedSprite animation;
	bool noKeyWasPressed = true;
	sf::Clock frameClock;
};

#endif