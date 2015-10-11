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

	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position, movement;
	sf::IntRect enemyRect;
	float speed;
	int lives;
	Animation *currentAnimation, walkingAnimationDown, walkingAnimationLeft;
	Animation walkingAnimationRight, walkingAnimationUp;
	AnimatedSprite animation;
	bool noKeyWasPressed = true;
	sf::Clock frameClock;
};

#endif