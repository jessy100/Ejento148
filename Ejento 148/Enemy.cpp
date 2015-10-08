// file Enemy.cpp

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "AnimatedSprite.h"
#include <string>
#include <iostream>

Enemy::Enemy(sf::Vector2f pos, float s, int l) :
	position(pos), speed(s), lives(l)
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
	walkingAnimationRight.addFrame(sf::IntRect(10, 0, 64, 80));
	walkingAnimationRight.addFrame(sf::IntRect(10, 170, 64, 80));
	walkingAnimationRight.addFrame(sf::IntRect(74, 170, 64, 80));
	walkingAnimationRight.addFrame(sf::IntRect(140, 170, 64, 80));
	walkingAnimationRight.addFrame(sf::IntRect(206, 170, 64, 80));

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

float Enemy::getSpeed() { return speed; }
void Enemy::setSpeed(float s) { speed = s; }
int Enemy::getLives() { return lives; }
void Enemy::setLives(int l) { lives = l; }
void Enemy::setAnimation(Animation &animation) { currentAnimation = &animation; }

void Enemy::draw(sf::RenderWindow &window) {
	window.draw(animation);
}

void Enemy::update(sf::RenderWindow &window) {
	sf::Time frameTime = frameClock.restart();
	enemyRect = sf::IntRect(animation.getPosition().x, animation.getPosition().y, 58, 80);

	movement = sf::Vector2f(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		setAnimation(walkingAnimationRight);
		movement.x += speed;
		noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		setAnimation(walkingAnimationRight);
		movement.x -= speed;
		noKeyWasPressed = false;
	}

	animation.play(*currentAnimation);
	animation.move(movement * frameTime.asSeconds());

	// if no key was pressed stop the animation
	if (noKeyWasPressed) { animation.stop(); }
	noKeyWasPressed = true;

	// Update the animation and draw it
	animation.update(frameTime);
	draw(window);
}

bool Enemy::CheckCollision(sf::IntRect collider) {
	if (collider.intersects(enemyRect)) {
		animation.setPosition(animation.getPosition().x, collider.top - 80);
		return true;
	}
	else {
		animation.move(sf::Vector2f(0, 0.1));
		return false;
	}
}
