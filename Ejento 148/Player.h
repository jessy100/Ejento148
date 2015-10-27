#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "AnimatedSprite.h"
#include "Audio.h"

class Player {
public:
	Player(sf::Vector2f, std::string n, int l);

	std::string Player::getName() { return name; }
	void Player::setName(std::string s) { name = s; }
	float Player::getSpeed() { return speed; }
	void Player::setSpeed(float s) { speed = s; }
	int Player::getLives() { return lives; }
	void Player::setLives(int l) { lives = l; }
	int Player::getDamage() { return playerDamage; }
	void Player::setDamage(int d) { playerDamage = d; }
	int Player::getHealth() { return playerHealth; }
	void Player::setHealth(int h) { playerHealth = h; }
	void Player::setAnimation(Animation &animation) { currentAnimation = &animation; }
	sf::IntRect Player::getRect() { return playerRect; }

	void CheckCollision(sf::IntRect);
	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
private:
	sf::Texture texture;
	sf::Vector2f position, velocity = sf::Vector2f(0,0);
	sf::IntRect playerRect;
	std::string name;

	const float gravity = 10.0f;
	float speed = 200.0f;
	float jumpSpeed = 600.0f;
	int lives,
		playerHealth = 10,
		playerHeight = 32, 
		playerWidth = 32, 
		playerDamage = 1;
	bool noKeyWasPressed = true, 
		grounded = false, 
		jumping = false;

	Animation *currentAnimation, 
			walkingAnimationDown, 
			walkingAnimationLeft;
	Animation walkingAnimationRight, walkingAnimationUp;
	AnimatedSprite animation;
	sf::Clock frameClock;
};

#endif