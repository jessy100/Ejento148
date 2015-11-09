#ifndef _BULLET_HPP
#define _BULLET_HPP

#include <SFML/Graphics.hpp>
#include "Player.h"

class Bullet {
public:

	/** \brief Constructor of Bullet.
	* \details Creates Bullet instance.
	* \param position the (start)position of the bullet
	* \param direction the direction of the bullet
	*/
	Bullet(sf::Vector2f, std::string);

	
	bool hasHit() { return impact; }
	
	/** \brief draws the Bullet
	* \details draws the Bullet with its current animation
	* \Param window the sf::RenderWindow reference.
	*/
	void draw(sf::RenderWindow &window);

	/** \brief Updates the Bullet.
	* \details Updates the Bullet and handles all its actions.
	* \Param window the sf::RenderWindow reference.
	*/
	void update(sf::RenderWindow &window);

	/** \brief Checks collision of Bullet.
	* \details checks the collision of the Bullet hitbox with the given intrect in the parameter
	* \param player the player instance
	*/
	void CheckCollision(Player &);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::IntRect bulletRect;

	int bulletHeight = 10,
		bulletWidth = 10, 
		bulletSpeed = 2;

	bool impact = false;
	std::string direction;
};

#endif