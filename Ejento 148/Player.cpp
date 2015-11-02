// file Player.cpp

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AnimatedSprite.h"
#include "Audio.h"
#include <string>
#include <iostream>

Player::Player(sf::Vector2f pos, std::string n,  int l) : 
	position(pos), name(n),  lives(l)
{
	if (!texture.loadFromFile("resources/images/ninja.png")) {
		std::cout << "Failed to load player spritesheet!" << std::endl;
	}

	// Set up the animations for all four directions (set spritesheet and push frames)

	// Idle right
	idleAnimationRight.setSpriteSheet(texture);
	idleAnimationRight.addFrame(sf::IntRect(128, 186, playerHeight, playerWidth));

	// Idle left
	idleAnimationLeft.setSpriteSheet(texture);
	idleAnimationLeft.addFrame(sf::IntRect(64, 687, playerHeight, playerWidth));

	// Crawl/duck/lie down
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, playerHeight, playerWidth));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, playerHeight, playerWidth));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, playerHeight, playerWidth));
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, playerHeight, playerWidth));

	// Walk left
	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(0, 555, playerHeight, playerWidth));
	walkingAnimationLeft.addFrame(sf::IntRect(192, 619, playerHeight, playerWidth));
	walkingAnimationLeft.addFrame(sf::IntRect(128, 619, playerHeight, playerWidth));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 619, playerHeight, playerWidth));
	walkingAnimationLeft.addFrame(sf::IntRect(0, 619, playerHeight, playerWidth));
	walkingAnimationLeft.addFrame(sf::IntRect(192, 683, playerHeight, playerWidth));

	// Walk right
	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(192, 53, playerHeight, playerWidth));
	walkingAnimationRight.addFrame(sf::IntRect(0, 117, playerHeight, playerWidth));
	walkingAnimationRight.addFrame(sf::IntRect(64, 117, playerHeight, playerWidth));
	walkingAnimationRight.addFrame(sf::IntRect(128, 117, playerHeight, playerWidth));
	walkingAnimationRight.addFrame(sf::IntRect(192, 117, playerHeight, playerWidth));
	walkingAnimationRight.addFrame(sf::IntRect(0, 181, playerHeight, playerWidth));

	// Swing weapon right
	swingAnimationRight.setSpriteSheet(texture);
	//swingAnimationRight.addFrame(sf::IntRect(64, 314, playerHeight, playerWidth));
	swingAnimationRight.addFrame(sf::IntRect(128, 314, playerHeight, playerWidth));
	swingAnimationRight.addFrame(sf::IntRect(192, 314, playerHeight, playerWidth));
	swingAnimationRight.addFrame(sf::IntRect(0, 378, playerHeight, playerWidth));

	// Swing weapon left
	swingAnimationLeft.setSpriteSheet(texture);
	//swingAnimationLeft.addFrame(sf::IntRect(128, 815, playerHeight, playerWidth));
	swingAnimationLeft.addFrame(sf::IntRect(64, 815, playerHeight, playerWidth));
	swingAnimationLeft.addFrame(sf::IntRect(0, 815, playerHeight, playerWidth));
	swingAnimationLeft.addFrame(sf::IntRect(192, 879, playerHeight, playerWidth));

	// Jump right
	jumpAnimationRight.setSpriteSheet(texture);
	jumpAnimationRight.addFrame(sf::IntRect(192, 53, playerHeight, playerWidth));

	// Jump left
	jumpAnimationLeft.setSpriteSheet(texture);
	jumpAnimationLeft.addFrame(sf::IntRect(0, 555, playerHeight, playerWidth));

	currentAnimation = &walkingAnimationDown;

	// Set up AnimatedSprite
	AnimatedSprite animation(sf::seconds((float)0.2), true, false);
	animation.setPosition(position);
}

void Player::update(sf::RenderWindow &window) {
	sf::Time frameTime = frameClock.restart();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && grounded) {
		// Jump
		Audio::PlaySound("jump.wav", 6, 0);
		if (direction == right) {
			setAnimation(jumpAnimationRight);
		} else {
			setAnimation(jumpAnimationLeft);
		}
		velocity.y -= jumpSpeed;
		noKeyWasPressed = false;
		grounded = false;
		jumping = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		// Duck/Crawl
		setAnimation(walkingAnimationDown);
		noKeyWasPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		direction = Direction::left;
		if (grounded == true && swingingWeapon == false) {
			setAnimation(walkingAnimationLeft);
		}
		velocity.x = -speed;
		noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		direction = Direction::right;
		if (grounded == true && swingingWeapon == false) {
			setAnimation(walkingAnimationRight);
		}
		velocity.x = speed;
		noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		// Check if the player can swing his weapon
		if (canSwingWeapon == true) {
			// Reset the clock
			swingWeaponClock.restart();

			// Call function to swing weapon
			SwingSword();

			canSwingWeapon = false;
		} else {
			// Check if 2 seconds have passed
			swingWeaponTime = swingWeaponClock.getElapsedTime();
			if (swingWeaponTime.asSeconds() > attackSpeed) {
				// If so, set canSwingWeapon to true
				canSwingWeapon = true;
			}
		}
		noKeyWasPressed = false;
	}

	if (swingingWeapon == false) {
		// Hide the hitbox of the weapon outside of the level
		weaponRect = sf::IntRect(
			-100,
			0,
			weaponRange,
			weaponArc
		);
	}

	// Update the position of the player collision box
	playerRect = sf::IntRect(
		animation.getPosition().x,
		animation.getPosition().y,
		playerHeight,
		playerWidth);

	animation.move(velocity * frameTime.asSeconds());
	animation.play(*currentAnimation);

	if (grounded == false) {
		velocity.y += gravity;
	}

	// Check if the player has swung a weapon and for how long
	if (swingingWeapon == true) {

		// If so, perform swing animation in the proper direction
		if (direction == right) {
			setAnimation(swingAnimationRight);
		} else {
			setAnimation(swingAnimationLeft);
		}

		// Check how long the player has swung his weapon
		swingAnimationTime = swingAnimationClock.getElapsedTime();
		if (swingAnimationTime.asSeconds() > attackSpeed) {
			// Stop swinging the weapon
			swingingWeapon = false;
		}
	}

	// If no key was pressed stop the animation
	if (noKeyWasPressed) { 
		if (direction == right && swingingWeapon == false && grounded == true) {
			setAnimation(idleAnimationRight);
		} else if(direction == left && swingingWeapon == false && grounded == true) {
			setAnimation(idleAnimationLeft);
		}
		velocity.x = 0;
	}
	noKeyWasPressed = true;

	// Update the animation and draw it
	animation.update(frameTime);

	position = animation.getPosition();

	if (position.y > (640 - playerHeight)) {
		grounded = true;
		velocity.y = 0;
	}

	draw(window);
}

void Player::draw(sf::RenderWindow &window) {
	window.draw(animation);
}

void Player::CheckCollision(sf::IntRect collider) {
	if (collider.intersects(playerRect)) {
		if (velocity.y > 0) {
			grounded = true;
			jumping = false;
			animation.setPosition(animation.getPosition().x,
				collider.top - playerHeight);
		}	
		velocity.y = 0;
	}
}

void Player::SwingSword() {
	// Player is swinging the weapon
	swingingWeapon = true;

	// Restart the clocks to keep tracking of the time it takes to swing a weapon
	swingWeaponClock.restart();
	swingAnimationClock.restart();

	// Perform swing animation
	if (direction == right) {
		// Deal damage to any entity within weaponRange pixels to the right side
		weaponRect = sf::IntRect(
			animation.getPosition().x + (playerWidth / 2),
			animation.getPosition().y + (playerHeight / 3),
			weaponArc,
			weaponRange
		);
	} else if (direction == left) {
		// Deal damage to any entity within weaponRange pixels to the left side
		weaponRect = sf::IntRect(
			animation.getPosition().x,
			animation.getPosition().y + (playerHeight / 3),
			weaponArc,
			weaponRange
		);
	}
}
