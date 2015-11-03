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
	rectshape.setPosition(sf::Vector2f(pos.x + 20, pos.y + 20));
	rectshape.setFillColor(sf::Color::Red);
	rectshape.setSize(sf::Vector2f(20, 35));

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

	// Die left
	deathAnimationLeft.setSpriteSheet(texture);
	deathAnimationLeft.addFrame(sf::IntRect(192, 502, playerHeight, playerWidth));
	deathAnimationLeft.addFrame(sf::IntRect(128, 502, playerHeight, playerWidth));
	deathAnimationLeft.addFrame(sf::IntRect(64, 502, playerHeight, playerWidth));
	deathAnimationLeft.addFrame(sf::IntRect(0, 502, playerHeight, playerWidth));
	deathAnimationLeft.addFrame(sf::IntRect(192, 566, playerHeight, playerWidth));
	deathAnimationLeft.addFrame(sf::IntRect(128, 566, playerHeight, playerWidth));
	deathAnimationLeft.addFrame(sf::IntRect(64, 566, playerHeight, playerWidth));

	// Die right
	deathAnimationRight.setSpriteSheet(texture);
	deathAnimationRight.addFrame(sf::IntRect(0, 0, playerHeight, playerWidth));
	deathAnimationRight.addFrame(sf::IntRect(64, 0, playerHeight, playerWidth));
	deathAnimationRight.addFrame(sf::IntRect(128, 0, playerHeight, playerWidth));
	deathAnimationRight.addFrame(sf::IntRect(192, 0, playerHeight, playerWidth));
	deathAnimationRight.addFrame(sf::IntRect(0, 64, playerHeight, playerWidth));
	deathAnimationRight.addFrame(sf::IntRect(64, 64, playerHeight, playerWidth));
	deathAnimationRight.addFrame(sf::IntRect(128, 64, playerHeight, playerWidth));

	currentAnimation = &idleAnimationRight;

	// Set up AnimatedSprite
	AnimatedSprite animation(sf::seconds((float)0.2), true, false);
	animation.setPosition(position);
}

void Player::update(sf::RenderWindow &window) {
	sf::Time frameTime = frameClock.restart();

	/*
		Player input
	*/
	if (dead == false) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && grounded 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::W) && onPlatform) {
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
			onPlatform = false;
			jumping = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			direction = Direction::left;
			if (swingingWeapon == false) {
				setAnimation(walkingAnimationLeft);
			}
			velocity.x = -speed;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			direction = Direction::right;
			if (swingingWeapon == false) {
				setAnimation(walkingAnimationRight);
			}
			velocity.x = speed;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			// Check if the player can swing his weapon
			if (canSwingWeapon == true) {
				// Call function to swing weapon
				SwingSword();

				canSwingWeapon = false;
			} else {
				// Check if x seconds have passed
				swingWeaponTime = swingWeaponClock.getElapsedTime();
				if (swingWeaponTime.asSeconds() > attackSpeed) {
					// If so, set canSwingWeapon to true
					canSwingWeapon = true;
				}
			}
			noKeyWasPressed = false;
		} // End player input

	} // End if dead == false

	// If the player has reached 0 health, play the death animation
	if (playerHealth <= 0) {
		// R.I.P.
		if (dead == false) {
			deathAnimationClock.restart();
			dead = true;
		}

		if (direction == left) {
			setAnimation(deathAnimationLeft);
		} else {
			setAnimation(deathAnimationRight);
		}

		// Check if x seconds have passed
		deathAnimationTime = deathAnimationClock.getElapsedTime();
		if (deathAnimationTime.asSeconds() > deathDuration) {
			// If so, the animation is finished and the game is over
			GameOver();
		}
	}

	// If the player is not swinging his weapon, move the hitbox somewhere out of the way
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
		animation.getPosition().x + 25,
		animation.getPosition().y + 28,
		20,
		35);

	
	// Update and play the animation
	animation.move(velocity * frameTime.asSeconds());
	animation.play(*currentAnimation);

	// Apply gravity
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
	if (noKeyWasPressed && swingingWeapon == false  && dead == false) {
		if (direction == right) {
			setAnimation(idleAnimationRight);
		} else if(direction == left) {
			setAnimation(idleAnimationLeft);
		}
		velocity.x = 0;
	}
	noKeyWasPressed = true;

	// Update the animation and draw it
	animation.update(frameTime);

	position = animation.getPosition();
	rectshape.setPosition(sf::Vector2f(position.x + 20, position.y + 25));

	if (position.y > (635 - playerHeight)) {
		grounded = true;
		onPlatform = false;
		position.y = (640 - playerHeight);
		velocity.y = 0;
	}

	draw(window);
}

void Player::draw(sf::RenderWindow &window) {
	window.draw(animation);
	//window.draw(rectshape);
}

void Player::CheckCollision(sf::IntRect collider) {

	
	if (collider.top >= playerRect.top) {

		//animation.setPosition(animation.getPosition().x, collider.top );
		velocity.y = 0;
		onPlatform = true;
	}
	if (collider.top <= playerRect.top) {
			velocity.y = gravity + 100;

	}
	if (collider.left > playerRect.left + playerRect.width) {
		velocity.x = 0;
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

void Player::GameOver() {
	// The player has died. End the game and show the post-game screen
}