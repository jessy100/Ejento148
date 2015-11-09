/*!
*   @author     Jessy Visch
*   @project    Themaopdracht 5, Ejento 148
*   @brief      Super class for background and interactive tiles
*/

#ifndef _BACKGROUND_HPP
#define _BACKGROUND_HPP

#include "SFML\Graphics.hpp"
#include <string>
#include "Tile.h"

class BackgroundTile : public Tile {
public:

	/** \brief Draws the Backgroundtile
	* \details Draws the Backgroundtile on the sf::RenderWindow it gets by reference.
	* \param window the sf::RenderWindow reference.
	*/
	BackgroundTile(sf::Vector2f position, std::string tileLocation, sf::Vector2f texturePosition);

	/** \brief Draws the Interactivetile
	* \details Draws the Interactivetile on the sf::RenderWindow it gets by reference.
	* \param window the sf::RenderWindow reference.
	*/
	void draw(sf::RenderWindow &window) override;

	/** \brief Returns the type of the tile
	* \details Returns type of the tile based on the type variable.
	*/
	virtual std::string getType() override { return type; };

private:
	sf::Vector2f position, texturePosition;
	sf::Sprite sprite;
	sf::Texture texture;
	std::string tileLocation;
	int tileSize = 128;
	std::string type = "BackgroundTile";


};

#endif