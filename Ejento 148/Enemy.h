#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Animation.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include "Bullet.h"

class Enemy {
public:
	enum Direction { left, right };
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
	void ShootWeapon();
private:
	sf::Texture texture;
	sf::Vector2f position, velocity = sf::Vector2f(0, 0), spawnPoint;
	sf::IntRect enemyRect;

	const float gravity = 10.0f,
		hitTimer = 0.8f,
		fallDuration = 1.7f,
		shotDelay = 1.5f;
	float speed = 1000.0f,
		jumpSpeed = 600.0f;

	int enemyHealth, 
		enemyWidth = 35, 
		deathWidth = 49,
		enemyHeight = 56,
		walkDistance = 100,
		bulletRange = 200,
		viewRange = 300, 
		heightDifference = 20; // Difference in height between the enemy and player

	bool grounded = false,
		invulnerable = false, 
		killed = false,
		falling = false, 
		canShoot = true;

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
	sf::Clock frameClock,
		invulernabilityClock,
		actionClock,
		shootClock,
		deathAnimationClock;

	sf::Time invulnerabilityTime,
		actionTime,
		shootTime,
		deathAnimationTime;

	enum State { idle, 
		shooting, 
		patrol, 
		dying 
	};
	State state = State::patrol;
	Direction direction = Direction::right;

	// Create a vector
	std::vector<Bullet *> bullets;
};

#endif