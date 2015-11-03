// file Enemy.cpp

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "AnimatedSprite.h"
#include <string>
#include <iostream>

Enemy::Enemy(sf::Vector2f pos, float s, int h) :
	position(pos), speed(s), enemyHealth(h)
{
	if (!texture.loadFromFile("resources/images/enemy.png")) {
		std::cout << "Failed to load enemy spritesheet!" << std::endl;
	}

	// Set up the animations for all four directions (set spritesheet and push frames)
	// Idle left
	idleAnimationLeft.setSpriteSheet(texture);
	idleAnimationLeft.addFrame(sf::IntRect(530, 105, enemyWidth, enemyHeight));

	// Idle right
	idleAnimationRight.setSpriteSheet(texture);
	idleAnimationRight.addFrame(sf::IntRect(0, 0, enemyWidth, enemyHeight));

	// Shooting left
	shootingAnimationLeft.setSpriteSheet(texture);
	shootingAnimationLeft.addFrame(sf::IntRect(252, 418, enemyWidth, enemyHeight));
	//shootingAnimationLeft.addFrame(sf::IntRect(188, 418, enemyWidth, enemyHeight));
	//shootingAnimationLeft.addFrame(sf::IntRect(134, 418, enemyWidth, enemyHeight));
	//shootingAnimationLeft.addFrame(sf::IntRect(91, 418, enemyWidth, enemyHeight));

	// Shooting right
	shootingAnimationRight.setSpriteSheet(texture);
	shootingAnimationRight.addFrame(sf::IntRect(10, 0, enemyWidth, enemyHeight));
	//shootingAnimationRight.addFrame(sf::IntRect(62, 0, enemyWidth, enemyHeight));
	//shootingAnimationRight.addFrame(sf::IntRect(115, 0, enemyWidth, enemyHeight));
	//shootingAnimationRight.addFrame(sf::IntRect(171, 0, enemyWidth, enemyHeight));

	// Dying left
	dyingAnimationLeft.setSpriteSheet(texture);
	dyingAnimationLeft.addFrame(sf::IntRect(660, 130, enemyWidth, enemyHeight));

	// Dying right
	dyingAnimationRight.setSpriteSheet(texture);
	dyingAnimationRight.addFrame(sf::IntRect(660, 130, enemyWidth, enemyHeight));

	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	//walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
	//walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	//walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));

	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(10, 124, enemyWidth, enemyHeight));
	//walkingAnimationRight.addFrame(sf::IntRect(51, 124, enemyWidth, enemyHeight));
	//walkingAnimationRight.addFrame(sf::IntRect(101, 124, enemyWidth, enemyHeight));
	//walkingAnimationRight.addFrame(sf::IntRect(152, 124, enemyWidth, enemyHeight));
	//walkingAnimationRight.addFrame(sf::IntRect(200, 124, enemyWidth, enemyHeight));
	//walkingAnimationRight.addFrame(sf::IntRect(253, 124, enemyWidth, enemyHeight));

	currentAnimation = &idleAnimationLeft;

	// Save the spawnpoint of the enemy unit
	spawnPoint = position;

	// Set up AnimatedSprite
	AnimatedSprite animation(sf::seconds((float)0.2), true, false);
	animation.setPosition(position);
}

void Enemy::draw(sf::RenderWindow &window) {
	window.draw(animation);
}

void Enemy::update(sf::RenderWindow &window) {
	if (killed == false) {
		sf::Time frameTime = frameClock.restart();

		// Update the collision rectangle
		enemyRect = sf::IntRect(animation.getPosition().x,
			animation.getPosition().y,
			enemyWidth,
			enemyHeight);

		position = animation.getPosition();

		// Update the enemy's current state based off environment
		updateState();

		/*
			Perform an action based on the enemy's current state
		*/
		switch (state) {
			case idle:
				if (direction == left) {
					setAnimation(idleAnimationLeft);
				} else {
					setAnimation(idleAnimationRight);
				}
				break;
			case shooting:
				if (direction == left) {
					setAnimation(shootingAnimationLeft);
				} else {
					setAnimation(shootingAnimationRight);
				}
				break;
			case patrol:
				if (direction == left) {
					setAnimation(walkingAnimationLeft);
					velocity.x = -speed;
				} else {
					setAnimation(walkingAnimationRight);
					velocity.x = speed;
				}
				break;
			case dying:
				if (direction == left) {
					setAnimation(dyingAnimationLeft);
				} else {
					setAnimation(dyingAnimationLeft);
				}
				// Set killed to true
				break;
		}

		animation.play(*currentAnimation);
		animation.move(velocity * frameTime.asSeconds());

		// Apply gravity
		if (grounded == false) { velocity.y += gravity; }
	
		if (position.y > 300) {
			grounded = true;
			velocity.y = 0;
		}

		// Update the animation and draw it
		animation.update(frameTime);
		draw(window);
	}
}

void Enemy::updateState() {
	// Check if the enemy's health has been reduced to 0
	if (enemyHealth == 0) { state = State::dying; }

	// Check if the player is within shooting range of the enemy
	// If so, perform a shot in the player direction
	// If the player is out of range and the enemy is not shooting, move closer


	// Make the enemy unit patrol near his spawnpoint
	if (state == patrol && position.x < (spawnPoint.x - walkDistance)) {
		direction = right;
	} else if (state == patrol && position.x > (spawnPoint.x + walkDistance)) {
		direction = left;
	}
}

void Enemy::takeDamage(Player &player) {
	if (invulnerable == false) {
		invulernabilityClock.restart();

		enemyHealth -= player.getDamage();
		invulnerable = true;
	} else {
		// Check how long it has been since being hit
		invulnerabilityTime = invulernabilityClock.getElapsedTime();

		if (invulnerabilityTime.asSeconds() > hitTimer) {
			invulnerable = false;
		}
	}
}

void Enemy::CheckCollision(Player &player) {
	if (player.getWeaponRect().intersects(enemyRect)) {
		takeDamage(player);
	}
}