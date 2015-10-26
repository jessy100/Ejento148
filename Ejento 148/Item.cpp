// file Player.cpp

#include <SFML/Graphics.hpp>
#include "Item.h"
#include "AnimatedSprite.h"
#include <string>
#include <iostream>

Item::Item(sf::Vector2f pos, std::string e, int l) :
	position(pos), effect(e), lives(l)
{
	if (effect == "damage") {
		if (!texture.loadFromFile("resources/images/weapon-item.png")) {
			std::cout << "Failed to load damage-item sprite!" << std::endl;
		}
	} else if (effect == "health") {
		if (!texture.loadFromFile("resources/images/health-item.png")) {
			std::cout << "Failed to load health-item sprite!" << std::endl;
		}
	}


}

void Item::draw(sf::RenderWindow &window) {
	window.draw(sprite);
}

void Item::update(sf::RenderWindow &window) {
	itemRect = sf::IntRect(
		position.x,
		position.y,
		itemHeight,
		itemWidth);

	// Update the animation and draw it
	draw(window);
}

void Item::CheckCollision(sf::IntRect collider) {
	if (collider.intersects(itemRect)) {

	}
}
