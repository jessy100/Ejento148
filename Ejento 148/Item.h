/*!
*   @author     Aydin Biber
*   @project    Themaopdracht 5, Ejento 148
*   @brief      The code for showing the leaderboards
*/

#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <SFML/Graphics.hpp>
#include "Player.h"

class Item {
public:
	
	/** \brief Constructor of item.
	* \details Creates item instance.
	* \param position the position of the item
	* \param name the name of the item
	*/
	Item(sf::Vector2f, std::string n);

	/** \brief Draws the item
	* \details Draws the item on the sf::RenderWindow it gets by reference.
	* \param window the sf::RenderWindow reference.
	*/
	void draw(sf::RenderWindow &window);

	/** \brief Checks collision with player
	* \details check collision with the player, if true removes the item from the level.
	* \param player the player reference.
	*/
	void CheckCollision(Player &);

	bool isLooted() { return looted; }

	/** \brief Sets item position.
	*/
	void setPosition(sf::Vector2f p) { position = p; }
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::IntRect itemRect;
	std::string effect;

	int itemHeight = 16,
		itemWidth = 16;

	bool looted = false;
};

#endif