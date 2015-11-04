#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "AnimatedSprite.h"
#include "Player.h"

class Enemy {
public:
	Enemy() {}
	Enemy(sf::Vector2f, float s, int h);

	float Enemy::getSpeed() { return speed; }
	void Enemy::setSpeed(float s) { speed = s; }
	int Enemy::getHealth() { return enemyHealth; }
	void Enemy::setHealth(int h) { enemyHealth = h; }
	void Enemy::setPosition(sf::Vector2f p) { position = p; }
	void Enemy::setAnimation(Animation &animation) { currentAnimation = &animation; }
	bool Enemy::isKilled() { return killed; }

	void CheckCollision(Player &player);
	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window, Player &);
	void Enemy::TakeDamage(Player &);
	void UpdateState(Player &);
private:
	sf::Texture texture;
	sf::Vector2f position, velocity = sf::Vector2f(0, 0), spawnPoint;
	sf::IntRect enemyRect;

	const float gravity = 10.0f, 
		hitTimer = 0.8f;
	float speed = 1000.0f,
		jumpSpeed = 600.0f;

	int enemyHealth, 
		enemyWidth = 42, 
		enemyHeight = 64,
		walkDistance = 100,
		bulletRange = 200,
		viewRange = 300;

	bool grounded = false,
		invulnerable = false, 
		killed = false;

	Animation *currentAnimation,
		walkingAnimationLeft, 
		walkingAnimationRight, 
		idleAnimationLeft, 
		idleAnimationRight,
		shootingAnimationLeft, 
		shootingAnimationRight, 
		dyingAnimationLeft, 
		dyingAnimationRight;

	AnimatedSprite animation;
	sf::Clock frameClock, invulernabilityClock, actionClock;
	sf::Time invulnerabilityTime, actionTime;

	enum State { idle, 
		shooting, 
		patrol, 
		dying 
	};
	State state = State::patrol;

	enum Direction { left, right };
	Direction direction = Direction::right;
};

#endif