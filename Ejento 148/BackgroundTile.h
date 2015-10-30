#ifndef _BACKGROUND_HPP
#define _BACKGROUND_HPP

#include "SFML\Graphics.hpp"
#include <string>
#include "Tile.h"

class BackgroundTile : public Tile {
public:

	BackgroundTile(sf::Vector2f position, std::string tileLocation, sf::Vector2f texturePosition);

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