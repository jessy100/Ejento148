#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "AnimatedSprite.h"

class Player {
public:
	Player(sf::Vector2f, std::string n, int l);

	std::string Player::getName() { return name; }
	void Player::setName(std::string s) { name = s; }
	float Player::getSpeed() { return speed; }
	void Player::setSpeed(float s) { speed = s; }
	int Player::getLives() { return lives; }
	sf::Vector2f Player::getPosition() { return position; }
	void Player::setLives(int l) { lives = l; }
	int Player::getDamage() { return playerDamage; }
	void Player::setDamage(int d) { playerDamage = d; }
	int Player::getHealth() { return playerHealth; }
	void Player::setHealth(int h) { playerHealth = h; }
	void Player::setAnimation(Animation &animation) { currentAnimation = &animation; }
	sf::IntRect Player::getWeaponRect() { return weaponRect; }
	sf::IntRect Player::getPlayerRect() { return playerRect; }
	

	void CheckCollision(sf::IntRect);
	void SwingSword();
	void GameOver();
	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
private:
	//test
	sf::RectangleShape rectshape;
	//testend
	sf::Texture texture;
	sf::Vector2f position, velocity = sf::Vector2f(0,0);
	sf::IntRect playerRect, 
				weaponRect;
	std::string name;

	const float gravity = 10.0f;
	float speed = 200.0f, jumpSpeed = 600.0f, attackSpeed = 0.5f, deathDuration = 1.4f;
	int lives,
		playerHealth = 10,
		playerHeight = 60, 
		playerCollisionHeight = 35,
		playerCollisionWidth = 50,
		playerWidth = 60, 
		playerDamage = 1, 
		weaponRange = 30, 
		weaponArc = 40;
	bool noKeyWasPressed = true, 
		grounded = false, 
		canSwingWeapon = true,
		swingingWeapon = false, 
		jumping = false, 
		dead = false,
		onPlatform = false;

	Animation *currentAnimation, 
		idleAnimationRight, 
		idleAnimationLeft, 
		walkingAnimationLeft,
		walkingAnimationRight,
		jumpAnimationRight,
		jumpAnimationLeft, 
		swingAnimationRight, 
		swingAnimationLeft, 
		deathAnimationLeft, 
		deathAnimationRight;

	AnimatedSprite animation;
	sf::Clock frameClock, swingWeaponClock, swingAnimationClock, deathAnimationClock;
	sf::Time swingWeaponTime, swingAnimationTime, deathAnimationTime;

	enum Direction {left, right};
	Direction direction = Direction::left;
};

#endif