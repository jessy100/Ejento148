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

	/** \brief Constructor of Enemy.
	* \details Creates Enemy instance.
	* \param position the position of the Enemy
	* \param speed the speed of the Enemy
	* \param lives the lives of the Enemy
	*/
	Enemy(sf::Vector2f, float s, int h);

	/** \brief Returns Enemy speed.
	*/
	float Enemy::getSpeed() { return speed; }

	/** \brief Sets Enemy speed.
	* \param speed the value which speed will be set to.
	*/
	void Enemy::setSpeed(float s) { speed = s; }

	/** \brief Returns Enemy Health
	*/
	int Enemy::getHealth() { return enemyHealth; }

	/** \brief Sets Enemy health.
	* \param health the value which health will be set to.
	*/
	void Enemy::setHealth(int h) { enemyHealth = h; }

	/** \brief Sets Enemy position.
	* \param position the value which position will be set to.
	*/
	void Enemy::setPosition(sf::Vector2f p) { position = p; }

	/** \brief Sets Enemy animation.
	* \param currentanimation the frame which the animation will be set to.
	*/
	void Enemy::setAnimation(Animation &animation) { currentAnimation = &animation; }

	bool Enemy::isKilled() { return killed; }

	/** \brief Checks collision of Enemy.
	* \details checks the collision of the Enemy hitbox with the given intrect in the parameter
	* \param player the player instance
	*/
	void CheckCollision(Player &player);

	/** \brief draws the Enemy
	* \details draws the Enemy with its current animation
	* \Param window the sf::RenderWindow reference.
	*/
	void draw(sf::RenderWindow &window);


	/** \brief Updates the Enemy.
	* \details Updates the Enemy and handles all its actions.
	* \Param window the sf::RenderWindow reference.
	* \Param player the player instance
	*/
	void update(sf::RenderWindow &window, Player &);

	/** \brief Lower Enemy health.
	* \details lower Enemy health with the amount given in the parameter.
	* \param amount the amount of damage he takes.
	*/
	void Enemy::TakeDamage(Player &);


	/** \brief Updates the Enemy.
	* \details Updates the Enemy and handles all its actions.
	* \Param window the sf::RenderWindow reference.
	*/
	void UpdateState(Player &);

	/** \brief Animation to shoot his gun
	*/
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
		walkDistance = 400,
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