#ifndef _INTERACTIVE_TILE_HPP
#define _INTERACTIVE_TILE_HPP

#include "SFML\Graphics.hpp"
#include <string>
#include "Tile.h"

class InteractiveTile : public Tile {
public:
	InteractiveTile(sf::Vector2f position, std::string tileLocation, sf::Vector2f texturePosition);
	void draw(sf::RenderWindow &window) override;
	virtual std::string getType() override { return type; };

private:
	sf::Vector2f position, texturePosition;
	sf::Sprite sprite;
	sf::Texture texture;
	std::string tileLocation;
	int tileSize = 128;
	std::string type = "InteractiveTile";


};

#endif