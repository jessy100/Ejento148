#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "AnimatedSprite.h"

class Enemy {
public:
	Enemy(sf::Vector2f, float s, int l);

	float Enemy::getSpeed() { return speed; }
	void Enemy::setSpeed(float s) { speed = s; }
	int Enemy::getLives() { return lives; }
	void Enemy::setLives(int l) { lives = l; }
	void Enemy::setAnimation(Animation &animation) { currentAnimation = &animation; }

	void CheckCollision(sf::IntRect);
	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
private:
	sf::Texture texture;
	sf::Vector2f position, velocity = sf::Vector2f(0, 0);
	sf::IntRect enemyRect;

	const float gravity = 10.0f;
	float speed = 1000.0f;
	float jumpSpeed = 600.0f;
	int lives, enemyHeight = 80, enemyWidth = 64;
	bool noKeyWasPressed = true, grounded = false, jumping = false;

	Animation *currentAnimation, walkingAnimationDown, walkingAnimationLeft;
	Animation walkingAnimationRight, walkingAnimationUp;
	AnimatedSprite animation;
	sf::Clock frameClock;
};

#endif