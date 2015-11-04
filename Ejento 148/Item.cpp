// file Player.cpp

#include <SFML/Graphics.hpp>
#include "Item.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include <string>
#include <iostream>
#include "ScoreCounter.h"

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

	sprite.setTexture(texture);
}

void Item::draw(sf::RenderWindow &window) {
	if (looted == false) {
		itemRect = sf::IntRect(
			position.x,
			position.y,
			itemWidth,
			itemHeight);

		sprite.setPosition(position);
		window.draw(sprite);
	}
}

void Item::CheckCollision(Player &player) {
	if (player.getPlayerRect().intersects(itemRect)) {
		if (effect == "damage") {
			player.setDamage(player.getDamage() + 1);
		} else if(effect == "health") {
			player.setHealth(player.getHealth() + 1);
		}
		ScoreCounter::increase(5);
		looted = true;
	}
}
