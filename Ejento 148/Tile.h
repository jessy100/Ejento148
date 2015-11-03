#ifndef _TILE_HPP
#define _TILE_HPP

#include "SFML\Graphics.hpp"
#include <string>

class Tile {

public:
	virtual void draw(sf::RenderWindow &window) {};
	virtual std::string getType() { return ""; };
	virtual sf::Vector2f getPosition() { return sf::Vector2f(0, 0); };
	virtual int getSize() { return 0; }
	virtual sf::IntRect getRect() { return sf::IntRect(999,999,999,999); }

};

#endif