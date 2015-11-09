/*!
*   @author     Aydin Biber
*   @project    Themaopdracht 5, Ejento 148
*   @brief      The code for everything to do with player.
*/

#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "AnimatedSprite.h"

class Player {
public:
	/** \brief Constructor of Player.
	* \details Creates Player instance.
	* \param position the position of the player
	* \param speed the speed of the player
	* \param lives the lives of the player
	*/
	Player(sf::Vector2f, std::string n, int l);

	/** \brief Returns player name
	*/
	std::string Player::getName() { return name; }
	
	/** \brief Sets player name.
	* \param name the value which name will be set to. 
	*/
	void Player::setName(std::string s) { name = s; }
	
	/** \brief Returns player speed.
	*/
	float Player::getSpeed() { return speed; }

	/** \brief Sets player speed.
	* \param speed the value which speed will be set to.
	*/
	void Player::setSpeed(float s) { speed = s; }

	/** \brief Returns player position
	*/
	sf::Vector2f Player::getPosition() { return position; }

	/** \brief Returns player Damage
	*/
	int Player::getDamage() { return playerDamage; }

	/** \brief Sets player speed.
	* \param speed the value which speed will be set to.
	*/
	void Player::setDamage(int d) { playerDamage = d; }

	/** \brief Returns player Health
	*/
	int Player::getHealth() { return playerHealth; }

	/** \brief Sets player health.
	* \param health the value which health will be set to.
	*/
	void Player::setHealth(int h) { playerHealth = h; }
	
	/** \brief Sets player animation.
	* \param currentanimation the frame which the animation will be set to.
	*/
	void Player::setAnimation(Animation &animation) { currentAnimation = &animation; }

	/** \brief Returns player weapon hitbox
	*/
	sf::IntRect Player::getWeaponRect() { return weaponRect; }

	/** \brief Returns player hitbox
	*/
	sf::IntRect Player::getPlayerRect() { return playerRect; }
	
	/** \brief Returns is player is dead
	*/
	bool Player::isDead() { return dead; }
	
	/** \brief Checks collision of player.
	* \details checks the collision of the player hitbox with the given intrect in the parameter 
	* \param collider the intrect it checks collides with.
	*/
	void CheckCollision(sf::IntRect);

	/** \brief Animation to swing the players sword
	*/
	void SwingSword();
	
	/** \brief Lower player health.
	* \details lower player health with the amount given in the parameter.
	* \param amaount the amount of damage takes.
	*/
	void TakeDamage(int);

	/** \brief Checks if player health is higher then 1
	*/
	void CheckPlayerHealth();

	/** \brief Moves character based on keyboard input
	*/
	void HandleKeyboardInput();

	/** \brief draws the players
	* \details draws the player with its current animation
	* \Param window the sf::RenderWindow reference.
	*/
	void draw(sf::RenderWindow &window);

	/** \brief Updates the player.
	* \details Updates the player and handles all its actions.
	* \Param window the sf::RenderWindow reference.
	*/
	void update(sf::RenderWindow &window);
private:
	//test
	sf::RectangleShape rectshape;
	//testend
	sf::Texture texture;
	sf::Vector2f position, velocity = sf::Vector2f(0,0);
	sf::IntRect playerRect, 
				weaponRect;
	std::string name;

	const float gravity = 10.0f,
		deathDuration = 1.2f; // Duration of the death animation

	float speed = 200.0f,
		jumpSpeed = 600.0f,
		attackSpeed = 0.5f; // Time between player attacks

	int playerHealth,
		playerHeight = 60, 
		playerWidth = 60,
		playerCollisionHeight = 35,
		playerCollisionWidth = 50,
		playerDamage = 1, 
		weaponRange = 30, 
		weaponArc = 40;

	bool noKeyWasPressed = true, 
		grounded = false, 
		canSwingWeapon = true,
		swingingWeapon = false, 
		jumping = false, 
		dying = false,
		dead = false,
		onPlatform = false;

	Animation *currentAnimation, 
		idleAnimationRight, 
		idleAnimationLeft, 
		walkingAnimationLeft,
		walkingAnimationRight,
		jumpAnimationRight,
		jumpAnimationLeft, 
		swingAnimationRight, 
		swingAnimationLeft, 
		deathAnimationLeft, 
		deathAnimationRight;

	AnimatedSprite animation;
	sf::Clock frameClock, 
		swingWeaponClock, 
		swingAnimationClock,
		deathAnimationClock;
	sf::Time swingWeaponTime, 
		swingAnimationTime,
		deathAnimationTime;

	enum Direction {left, right};
	Direction direction = Direction::left;
};

#endif