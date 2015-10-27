// file Player.cpp

#include <SFML/Graphics.hpp>
#include "Item.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include <string>
#include <iostream>

Item::Item(sf::Vector2f pos, std::string e) :
	position(pos), effect(e)
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

	itemRect = sf::IntRect(
		position.x,
		position.y,
		itemHeight,
		itemWidth);

	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Item::draw(sf::RenderWindow &window) {
	window.draw(sprite);
}

bool Item::CheckCollision(Player &player) {
	if (player.getRect().intersects(itemRect)) {
		if (effect == "damage") {
			player.setDamage(player.getDamage() + 1);
			std::cout << "Player picked up a weapon\n";
			std::cout << "Player damage is now " << player.getDamage() << "\n";
		} else if(effect == "health") {
			player.setHealth(player.getHealth() + 1);
			std::cout << "Player picked up health\n";
			std::cout << "Player health is now " << player.getHealth() << "\n";
		}
		return true;
	}
	return false;
}
