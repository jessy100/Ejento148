// file Bullet.cpp

#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Player.h"
#include <string>
#include <iostream>

Bullet::Bullet(sf::Vector2f pos, std::string d) :
	position(pos), direction(d)
{
	if (!texture.loadFromFile("resources/images/bullet.gif")) {
		std::cout << "Failed to load bullet sprite!" << std::endl;
	}

	sprite.setTexture(texture);
}

void Bullet::update(sf::RenderWindow &window) {
	if (impact == false) {
		bulletRect = sf::IntRect(
			position.x,
			position.y,
			bulletWidth,
			bulletHeight
		);

		if (direction == "left") {
			position.x -= bulletSpeed;
		} else {
			position.x += bulletSpeed;
		}

		sprite.setPosition(position);

		draw(window);
	}
}

void Bullet::draw(sf::RenderWindow &window) {
	window.draw(sprite);
}

void Bullet::CheckCollision(Player &player) {
	if (player.getPlayerRect().intersects(bulletRect)) {
		impact = true;
		player.TakeDamage(1);
	}
}
