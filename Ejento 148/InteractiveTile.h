/*!
*   @author     Jessy Visch
*   @project    Themaopdracht 5, Ejento 148
*   @brief      Super class for background and interactive tiles
*/

#ifndef _INTERACTIVE_TILE_HPP
#define _INTERACTIVE_TILE_HPP

#include "SFML\Graphics.hpp"
#include <string>
#include "Tile.h"

class InteractiveTile : public Tile {
public:
	InteractiveTile(sf::Vector2f position, std::string tileLocation, sf::Vector2f texturePosition);

	/** \brief Draws the Interactivetile
	* \details Draws the Interactivetile on the sf::RenderWindow it gets by reference.
	* \param window the sf::RenderWindow reference.
	*/
	void draw(sf::RenderWindow &window) override;

	/** \brief Returns the type of the tile
	* \details Returns type of the tile based on the type variable.
	*/
	std::string getType() override { return type; };

	/** \brief Returns the position of the tile.
	* \details Returns the position of the tile in the level.
	*/
	sf::Vector2f getPosition() override { return position; }

	/** \brief Returns the dimensions of the tile
	* \details Returns the dimension of the tile.
	*/
	int getSize() override { return size; }

	/** \brief Returns the IntRect of the tile,
	* \details Returns the position of the tile in the level.
	* this intrect is used for collision detection.
	*/
	sf::IntRect getRect() override;

private:
	sf::Vector2f position, texturePosition;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect rect;
	std::string tileLocation;

	//size of the tile in the spritesheet
	int tileSize = 128;
	//size is the size of the tile on screen
	int size = 32;
	std::string type = "InteractiveTile";


};

#endif