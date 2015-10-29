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

	// Jump
	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, playerHeight, playerWidth));
	walkingAnimationUp.addFrame(sf::IntRect(64, 96, playerHeight, playerWidth));
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, playerHeight, playerWidth));
	walkingAnimationUp.addFrame(sf::IntRect(0, 96, playerHeight, playerWidth));

	currentAnimation = &walkingAnimationDown;

	// Set up AnimatedSprite
	AnimatedSprite animation(sf::seconds((float)0.2), true, false);
	animation.setPosition(position);

	weapon.setSize(sf::Vector2f(weaponRange, weaponArc));
	weapon.setFillColor(sf::Color::Red);
}

void Player::update(sf::RenderWindow &window) {
	sf::Time frameTime = frameClock.restart();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && grounded) {
		// Jump
		Audio::PlaySound("jump.wav", 6, 0);
		setAnimation(walkingAnimationUp);
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
		setAnimation(walkingAnimationLeft);
		velocity.x = -speed;
		noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		direction = Direction::right;
		setAnimation(walkingAnimationRight);
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

	animation.play(*currentAnimation);

	// Hide the hitbox of the weapon outside of the level
	weaponRect = sf::IntRect(
		-100, 
		0, 
		weaponRange, 
		playerHeight
	);

	playerRect = sf::IntRect(
		animation.getPosition().x,
		animation.getPosition().y,
		playerHeight,
		playerWidth);
	animation.move(velocity * frameTime.asSeconds());

	if (grounded == false) {
		velocity.y += gravity;
	}

	// Check if the player has swung a weapon and for how long
	if (swingingWeapon == true) {
		swingAnimationTime = swingAnimationClock.getElapsedTime();
		if (swingAnimationTime.asSeconds() > attackSpeed) {
			// Stop swinging the weapon
			swingingWeapon = false;
		}
	}
	
	// If no key was pressed stop the animation
	if (noKeyWasPressed) { 
		if (direction == right && swingingWeapon == false) {
			setAnimation(idleAnimationRight);
		} else if(direction == left && swingingWeapon == false) {
			setAnimation(idleAnimationLeft);
		}
		velocity.x = 0;
	}
	noKeyWasPressed = true;

	// Update the animation and draw it
	animation.update(frameTime);

	position = animation.getPosition();
	draw(window);
}

void Player::draw(sf::RenderWindow &window) {
	// Test to visualise the weapon collision
	window.draw(weapon);

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
	// Start the clock
	swingWeaponClock.restart();

	// Perform swing animation
	if (direction == right) {
		setAnimation(swingAnimationRight);
		// Deal damage to any entity within weaponRange pixels to the right side
		weaponRect = sf::IntRect(
			animation.getPosition().x + (playerWidth / 2),
			animation.getPosition().y + (playerHeight / 3),
			weaponArc,
			weaponRange
		);

		// Test to visualise the weapon collision
		weapon.setPosition(sf::Vector2f(animation.getPosition().x + (playerWidth / 2), animation.getPosition().y + (playerHeight / 3)));

	} else if (direction == left) {
		setAnimation(swingAnimationLeft);
		// Deal damage to any entity within weaponRange pixels to the left side
		weaponRect = sf::IntRect(
			animation.getPosition().x,
			animation.getPosition().y + (playerHeight / 3),
			weaponArc,
			weaponRange
		);

		// Test to visualise the weapon collision
		weapon.setPosition(sf::Vector2f(animation.getPosition().x, animation.getPosition().y + (playerHeight / 3)));
	}
	std::cout << "You swing your sword for " << playerDamage << " damage\n";
}
