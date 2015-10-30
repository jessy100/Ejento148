// file Enemy.cpp

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "AnimatedSprite.h"
#include <string>
#include <iostream>

Enemy::Enemy(sf::Vector2f pos, float s, int h) :
	position(pos), speed(s), enemyHealth(h)
{
	if (!texture.loadFromFile("resources/images/enemy.jpg")) {
		std::cout << "Failed to load enemy spritesheet!" << std::endl;
	}

	// Set up the animations for all four directions (set spritesheet and push frames)
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(20, 4, 65, 75));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));

	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));

	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(10, 0, enemyWidth, enemyHeight));
	walkingAnimationRight.addFrame(sf::IntRect(10, 170, enemyWidth, enemyHeight));
	walkingAnimationRight.addFrame(sf::IntRect(74, 170, enemyWidth, enemyHeight));
	walkingAnimationRight.addFrame(sf::IntRect(140, 170, enemyWidth, enemyHeight));
	walkingAnimationRight.addFrame(sf::IntRect(206, 170, enemyWidth, enemyHeight));

	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));

	currentAnimation = &walkingAnimationRight;

	// Set up AnimatedSprite
	AnimatedSprite animation(sf::seconds((float)0.2), true, false);
	animation.setPosition(position);
}

void Enemy::draw(sf::RenderWindow &window) {
	window.draw(animation);
}

void Enemy::update(sf::RenderWindow &window) {
	if (dead == false) {
		sf::Time frameTime = frameClock.restart();

		// Update the collision rectangle
		enemyRect = sf::IntRect(animation.getPosition().x,
			animation.getPosition().y,
			enemyWidth,
			enemyHeight);

		position = animation.getPosition();
		/*
		Temporary input to test animations
		Will be replaced with AI system later
		*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			setAnimation(walkingAnimationRight);
			velocity.x = speed;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			setAnimation(walkingAnimationRight);
			velocity.x = -speed;
			noKeyWasPressed = false;
		}

		animation.play(*currentAnimation);
		animation.move(velocity * frameTime.asSeconds());

		if (grounded == false) {
			velocity.y += gravity;
		}

		if (position.y > 575) {
			grounded = true;
			velocity.y = 0;
		}

		// If no key was pressed stop the animation
		if (noKeyWasPressed) {
			animation.stop();
			velocity.x = 0;
		}
		noKeyWasPressed = true;

		// Update the animation and draw it
		animation.update(frameTime);
		draw(window);
	}
}

void Enemy::takeDamage(Player &player) {
	enemyHealth -= player.getDamage();
	std::cout << "Most recently hit enemy has " << enemyHealth << " health remaining";
}

void Enemy::CheckCollision(Player &player) {
	if (player.getWeaponRect().intersects(enemyRect)) {
		takeDamage(player);
	}
}