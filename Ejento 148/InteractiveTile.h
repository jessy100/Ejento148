#ifndef _INTERACTIVE_TILE_HPP
#define _INTERACTIVE_TILE_HPP

#include "SFML\Graphics.hpp"
#include <string>
#include "Tile.h"

class InteractiveTile : public Tile {
public:
	InteractiveTile(sf::Vector2f position, std::string tileLocation, sf::Vector2f texturePosition);
	void draw(sf::RenderWindow &window) override;
	std::string getType() override { return type; };
	sf::Vector2f getPosition() override { return position; }
	int getSize() override { return size; }
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