// file Player.cpp

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AnimatedSprite.h"
#include "Audio.h"
#include <string>
#include <iostream>

Player::Player(sf::Vector2f pos, std::string n,  int h) : 
	position(pos), name(n),  playerHealth(h)
{
	if (!texture.loadFromFile("resources/images/ninja.png")) {
		std::cout << "Failed to load player spritesheet!" << std::endl;
	}

	animation.setPosition(position);

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
}

void Player::update(sf::RenderWindow &window) {
	sf::Time frameTime = frameClock.restart();

	/*
		If the player character is not dying, input is permitted
	*/
	if (dying == false) {
		HandleKeyboardInput();
	} // End if(dying == false)

	// Check if the player is healthy
	CheckPlayerHealth();

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
		35
	);

	
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
	if (noKeyWasPressed && swingingWeapon == false  && dying == false) {
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
}

void Player::CheckCollision(sf::IntRect collider) {
	if (collider.top >= playerRect.top) {
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
	Audio::PlaySound("sword-attack.wav", 1, 0);
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

void Player::TakeDamage() {
	if (invulnerable == false) {
		invulernabilityClock.restart();

		// Enemy hits deal 1 damage
		playerHealth -= 1;
		invulnerable = true;
	}
	else {
		// Check how long it has been since being hit
		invulnerabilityTime = invulernabilityClock.getElapsedTime();

		if (invulnerabilityTime.asSeconds() > hitTimer) {
			invulnerable = false;
		}
	}
}

void Player::CheckPlayerHealth() {
	// If the player has reached 0 health, play the death animation
	if (playerHealth <= 0) {
		// Set the player's velocity to 0 so he doesn't slide while dying
		velocity.x = 0;
		velocity.y = 0;

		// R.I.P.
		if (dying == false) {
			deathAnimationClock.restart();
			dying = true;
		}

		if (direction == left) {
			setAnimation(deathAnimationLeft);
		}
		else {
			setAnimation(deathAnimationRight);
		}

		// Check if x seconds have passed
		deathAnimationTime = deathAnimationClock.getElapsedTime();
		if (deathAnimationTime.asSeconds() > deathDuration) {
			// If so, the animation is finished and the game is over
			dead = true;
		}
	}
}

void Player::HandleKeyboardInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && grounded
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::W) && onPlatform) {
		// Jump
		Audio::PlaySound("jump.wav", 3, 0);
		if (direction == right) {
			setAnimation(jumpAnimationRight);
		}
		else {
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
		swingWeaponTime = swingWeaponClock.getElapsedTime();
		if (swingWeaponTime.asSeconds() > attackSpeed) { // Check if x seconds have passed
			// If so, set canSwingWeapon to true
			SwingSword();
		}
		noKeyWasPressed = false;
	} // End player input
}