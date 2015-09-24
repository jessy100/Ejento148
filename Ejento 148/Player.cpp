// file Player.cpp

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AnimatedSprite.h"
#include <string>
#include <iostream>

Player::Player(sf::Vector2f pos, std::string n, float s, int l) : 
	position(pos), name(n), speed(s), lives(l)
{
	if (!texture.loadFromFile("resources/images/player.png")) {
		std::cout << "Failed to load player spritesheet!" << std::endl;
	}

	// Set up the animations for all four directions (set spritesheet and push frames)
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));

	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));

	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));

	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));

	currentAnimation = &walkingAnimationDown;

	// Set up AnimatedSprite
	AnimatedSprite animation(sf::seconds((float)0.2), true, false);
	animation.setPosition(sf::Vector2f(sf::Vector2i(1024, 768) / 2));
}

std::string Player::getName() { return name; }
void Player::setName(std::string s) { name = s; }
float Player::getSpeed() { return speed; }
void Player::setSpeed(float s) { speed = s; }
int Player::getLives() { return lives; }
void Player::setLives(int l) { lives = l; }
void Player::setAnimation(Animation &animation) { currentAnimation = &animation; }

void Player::draw(sf::RenderWindow &window) {
	// Draw a circle
	window.draw(animation);
}

void Player::update(sf::RenderWindow &window) {
	sf::Time frameTime = frameClock.restart();

	// If a key was pressed set the correct animation and move correctly
	// Move this to a proper inputhandler
	// Choppy movement atm
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		setAnimation(walkingAnimationUp);
		movement.y -= speed;
		noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		setAnimation(walkingAnimationDown);
		movement.y += speed;
		noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		setAnimation(walkingAnimationLeft);
		movement.x -= speed;
		noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		setAnimation(walkingAnimationRight);
		movement.x += speed;
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
