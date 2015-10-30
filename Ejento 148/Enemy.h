#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "AnimatedSprite.h"
#include "Player.h"

class Enemy {
public:
	Enemy(sf::Vector2f, float s, int h);

	float Enemy::getSpeed() { return speed; }
	void Enemy::setSpeed(float s) { speed = s; }
	int Enemy::getHealth() { return enemyHealth; }
	void Enemy::setHealth(int h) { enemyHealth = h; }
	void Enemy::setPosition(sf::Vector2f p) { position = p; }
	void Enemy::takeDamage(Player &);
	void Enemy::setAnimation(Animation &animation) { currentAnimation = &animation; }

	void CheckCollision(Player &player);
	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
private:
	sf::Texture texture;
	sf::Vector2f position, velocity = sf::Vector2f(0, 0);
	sf::IntRect enemyRect;

	const float gravity = 10.0f;
	float speed = 1000.0f, jumpSpeed = 600.0f;
	int enemyHealth, enemyHeight = 80, enemyWidth = 64;
	bool noKeyWasPressed = true, grounded = false, jumping = false, dead = false;

	Animation *currentAnimation, 
		walkingAnimationDown,
		walkingAnimationLeft, 
		walkingAnimationRight, 
		walkingAnimationUp;
	AnimatedSprite animation;
	sf::Clock frameClock;
};

#endif