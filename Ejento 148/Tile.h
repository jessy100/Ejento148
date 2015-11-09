/*!
*   @author     Jessy Visch
*   @project    Themaopdracht 5, Ejento 148
*   @brief      Super class for background and interactive tiles
*/

#ifndef _TILE_HPP
#define _TILE_HPP

#include "SFML\Graphics.hpp"
#include <string>

class Tile {

public:

	/** \brief Draws the tiles
	* \details Draws the tiles on the sf::RenderWindow it gets by reference.
	* \param window the sf::RenderWindow reference.
	*/
	virtual void draw(sf::RenderWindow &window) {};

	/** \brief Returns the type of the tile
	* \details Returns type of the tile based on childs value.
	*/
	virtual std::string getType() { return ""; };
	
	/** \brief Returns the position of the tile.
	* \details Returns the position of the tile in the level.
	*/
	virtual sf::Vector2f getPosition() { return sf::Vector2f(0, 0); };

	/** \brief Returns the dimensions of the tile
	* \details Returns the dimension of the tile.
	*/
	virtual int getSize() { return 0; }
	
	/** \brief Returns the IntRect of the tile,
	* \details Returns the position of the tile in the level.
	* this intrect is used for collision detection.
	*/
	virtual sf::IntRect getRect() { return sf::IntRect(999,999,999,999); }

};

#endif