// file Enemy.cpp

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "AnimatedSprite.h"
#include <string>
#include <iostream>
#include "ScoreCounter.h"

Enemy::Enemy(sf::Vector2f pos, float s, int h) :
	position(pos), speed(s), enemyHealth(h)
{
	if (!texture.loadFromFile("resources/images/enemy.png")) {
		std::cout << "Failed to load enemy spritesheet!" << std::endl;
	}

	animation.setPosition(position);

	// Set up the animations for all four directions (set spritesheet and push frames)
	// Idle left
	idleAnimationLeft.setSpriteSheet(texture);
	idleAnimationLeft.addFrame(sf::IntRect(250, 67, enemyWidth, enemyHeight));

	// Idle right
	idleAnimationRight.setSpriteSheet(texture);
	idleAnimationRight.addFrame(sf::IntRect(0, 0, enemyWidth, enemyHeight));

	// Shooting left
	shootingAnimationLeft.setSpriteSheet(texture);
	shootingAnimationLeft.addFrame(sf::IntRect(215, 396, enemyWidth, enemyHeight));

	// Shooting right
	shootingAnimationRight.setSpriteSheet(texture);
	shootingAnimationRight.addFrame(sf::IntRect(0, 396, enemyWidth, enemyHeight));

	// Dying left
	dyingAnimationLeft.setSpriteSheet(texture);
	dyingAnimationLeft.addFrame(sf::IntRect(200, 264, deathWidth, enemyHeight));
	dyingAnimationLeft.addFrame(sf::IntRect(150, 264, deathWidth, enemyHeight));
	dyingAnimationLeft.addFrame(sf::IntRect(100, 264, deathWidth, enemyHeight));
	dyingAnimationLeft.addFrame(sf::IntRect(51, 264, deathWidth, enemyHeight));
	dyingAnimationLeft.addFrame(sf::IntRect(0, 264, deathWidth, enemyHeight));
	dyingAnimationLeft.addFrame(sf::IntRect(200, 332, deathWidth, enemyHeight));
	dyingAnimationLeft.addFrame(sf::IntRect(150, 332, deathWidth, enemyHeight));
	dyingAnimationLeft.addFrame(sf::IntRect(100, 332, deathWidth, enemyHeight));
	dyingAnimationLeft.addFrame(sf::IntRect(51, 332, deathWidth, enemyHeight));

	// Dying right
	dyingAnimationRight.setSpriteSheet(texture);
	dyingAnimationRight.addFrame(sf::IntRect(0, 129, deathWidth, enemyHeight));
	dyingAnimationRight.addFrame(sf::IntRect(51, 129, deathWidth, enemyHeight));
	dyingAnimationRight.addFrame(sf::IntRect(100, 129, deathWidth, enemyHeight));
	dyingAnimationRight.addFrame(sf::IntRect(150, 129, deathWidth, enemyHeight));
	dyingAnimationRight.addFrame(sf::IntRect(200, 129, deathWidth, enemyHeight));
	dyingAnimationRight.addFrame(sf::IntRect(0, 198, deathWidth, enemyHeight));
	dyingAnimationRight.addFrame(sf::IntRect(50, 198, deathWidth, enemyHeight));
	dyingAnimationRight.addFrame(sf::IntRect(100, 198, deathWidth, enemyHeight));
	dyingAnimationRight.addFrame(sf::IntRect(150, 198, deathWidth, enemyHeight));

	// Walking left
	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(212, 56, enemyWidth, enemyHeight));
	walkingAnimationLeft.addFrame(sf::IntRect(170, 56, enemyWidth, enemyHeight));
	walkingAnimationLeft.addFrame(sf::IntRect(127, 56, enemyWidth, enemyHeight));
	walkingAnimationLeft.addFrame(sf::IntRect(85, 56, enemyWidth, enemyHeight));
	walkingAnimationLeft.addFrame(sf::IntRect(42, 56, enemyWidth, enemyHeight));
	walkingAnimationLeft.addFrame(sf::IntRect(0, 56, enemyWidth, enemyHeight));

	// Walking right
	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(0, 0, enemyWidth, enemyHeight));
	walkingAnimationRight.addFrame(sf::IntRect(42, 0, enemyWidth, enemyHeight));
	walkingAnimationRight.addFrame(sf::IntRect(85, 0, enemyWidth, enemyHeight));
	walkingAnimationRight.addFrame(sf::IntRect(127, 0, enemyWidth, enemyHeight));
	walkingAnimationRight.addFrame(sf::IntRect(170, 0, enemyWidth, enemyHeight));
	walkingAnimationRight.addFrame(sf::IntRect(212, 0, enemyWidth, enemyHeight));

	currentAnimation = &idleAnimationLeft;

	// Save the spawnpoint of the enemy unit
	spawnPoint = position;

	// Set up AnimatedSprite
	AnimatedSprite animation(sf::seconds((float)0.2), true, false);
}

void Enemy::draw(sf::RenderWindow &window) {
	window.draw(animation);
}

void Enemy::update(sf::RenderWindow &window, Player &player) {
	if (killed == false) {
		sf::Time frameTime = frameClock.restart();

		if (!bullets.empty()) {
			// Update the bullets
				// Loop through all bullets in the items vector
				for (std::vector<int>::size_type i = 0; i != bullets.size(); i++) {
					if (!bullets[i]->hasHit()) {
					bullets[i]->update(window);
					bullets[i]->CheckCollision(player);
				}
			}
		}

		// Update the collision rectangle
		enemyRect = sf::IntRect(animation.getPosition().x,
			animation.getPosition().y,
			enemyWidth,
			enemyHeight);

		position = animation.getPosition();

		// Update the enemy's current state based off environment
		UpdateState(player);

		/*
			Perform an action based on the enemy's current state
		*/
		switch (state) {
			case idle:
				if (direction == left) {
					setAnimation(idleAnimationLeft);
					velocity.x = 0;
				} else {
					setAnimation(idleAnimationRight);
					velocity.x = 0;
				}
				break;
			case shooting:
				if (direction == left) {
					setAnimation(shootingAnimationLeft);
					velocity.x = 0;
				} else {
					setAnimation(shootingAnimationRight);
					velocity.x = 0;
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
				if (falling == false) {
					deathAnimationClock.restart();
					ScoreCounter::increase(10);
					falling = true;
				}

				velocity.x = 0;

				if (direction == left) {
					setAnimation(dyingAnimationLeft);
					// Perform the left death animation for a set amount of time
				} else {
					setAnimation(dyingAnimationRight);
					// Perform the right death animation for a set amount of time
				}

				// Check if x seconds have passed
				deathAnimationTime = deathAnimationClock.getElapsedTime();
				if (deathAnimationTime.asSeconds() > fallDuration) {
					// Set killed to true once the death animation is done playing
					killed = true;
				}
				break;
		}

		animation.play(*currentAnimation);
		animation.move(velocity * frameTime.asSeconds());

		// Apply gravity
		if (grounded == false) { velocity.y += gravity; }
	
		if (position.y > (640 - enemyHeight)) {
			grounded = true;
			velocity.y = 0;
		}

		// Update the animation and draw it
		animation.update(frameTime);
		draw(window);
	}
}

void Enemy::TakeDamage(Player &player) {
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
		TakeDamage(player);
	}
}

void Enemy::UpdateState(Player &player) {
	// Check if the enemy's health has been reduced to 0
	if (enemyHealth <= 0) { 
		state = State::dying;
	} else {
		// Check if the player is within vertical viewing range of the enemy
		if ((player.getPosition().y + heightDifference) > animation.getPosition().y
			&& player.getPosition().y < (animation.getPosition().y + enemyHeight)) {
			// Check if the player within shooting range
			// To the right side of the enemy
			if (player.getPosition().x < (animation.getPosition().x + bulletRange)
				&& player.getPosition().x >(animation.getPosition().x)) {
				state = shooting;
				direction = right;

				ShootWeapon();
				// To the left side of the enemy
			} else if (player.getPosition().x > (animation.getPosition().x - bulletRange)
				&& player.getPosition().x < (animation.getPosition().x)) {
				state = shooting;
				direction = left;

				ShootWeapon();
			} else {
				state = patrol;
			}
		} else {
			state = patrol;
		}
	}


	// Make the enemy unit patrol near his spawnpoint
	if (state == patrol && position.x < (spawnPoint.x - walkDistance)) {
		direction = right;
	} else if (state == patrol && position.x > (spawnPoint.x + walkDistance)) {
		direction = left;
	}
}

void Enemy::ShootWeapon() {
	// Spawn a bullet every x seconds
	if (canShoot == true) {
		shootClock.restart();

		// Add a new bullet object to the bullets vector
		if (direction == left) {
			bullets.push_back(new Bullet(
				sf::Vector2f(animation.getPosition().x -10, animation.getPosition().y + 10),
				"left"
				)
			);
		} else {
			bullets.push_back(new Bullet(
				sf::Vector2f(animation.getPosition().x + enemyWidth, animation.getPosition().y + 10),
				"right"
				)
			);
		}

		canShoot = false;
	} else {
		// Check if x seconds have passed
		shootTime = shootClock.getElapsedTime();
		if (shootTime.asSeconds() > shotDelay) {
			// If so, the animation is finished and the game is over
			canShoot = true;
		}
	}
}