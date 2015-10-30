#ifndef _TILE_HPP
#define _TILE_HPP

#include "SFML\Graphics.hpp"
#include <string>

class Tile {

public:
	virtual void draw(sf::RenderWindow &window) {};
	virtual std::string getType() { return ""; };


};

#endif