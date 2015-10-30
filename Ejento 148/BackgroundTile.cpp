#include "SFML\Graphics.hpp"
#include <string>
#include "BackgroundTile.h"
#include <iostream>

BackgroundTile::BackgroundTile(sf::Vector2f position, std::string tileLocation, sf::Vector2f texturePosition) :
	position{ position },
	tileLocation{ tileLocation },
	texturePosition{ texturePosition }
{
	sprite.setPosition(position);
	texture.loadFromFile(tileLocation);
	sprite.setTexture(texture);
}

void BackgroundTile::draw(sf::RenderWindow &window) {
	sprite.setTextureRect(sf::IntRect(texturePosition.x * tileSize,
		texturePosition.y * tileSize,
		tileSize,
		tileSize));

	window.draw(sprite);
}