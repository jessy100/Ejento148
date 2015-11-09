#include "SFML\Graphics.hpp"
#include <string>
#include "InteractiveTile.h"
#include <iostream>

InteractiveTile::InteractiveTile(sf::Vector2f position, std::string tileLocation, sf::Vector2f texturePosition) :
	position{ position },
	tileLocation{ tileLocation },
	texturePosition{ texturePosition }
{
	sprite.setPosition(position);
	texture.loadFromFile(tileLocation);
	sprite.setTexture(texture);
}

void InteractiveTile::draw(sf::RenderWindow &window) {
	sprite.setTextureRect(sf::IntRect(texturePosition.x * tileSize,
		texturePosition.y * tileSize,
		size,
		size));
	sf::RectangleShape rs;
	rs.setSize(sf::Vector2f(size, size));
	rs.setPosition(position);
	window.draw(sprite);
	//window.draw(rs);
}

sf::IntRect InteractiveTile::getRect() {
	return sf::IntRect(position.x, position.y, size, size);
	
}