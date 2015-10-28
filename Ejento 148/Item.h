#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <SFML/Graphics.hpp>
#include "Player.h"

class Item {
public:
	Item(sf::Vector2f, std::string n);

	void draw(sf::RenderWindow &window);
	bool CheckCollision(Player &);

	void setPosition(sf::Vector2f p) { position = p; }
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::IntRect itemRect;
	std::string effect;

	int itemHeight = 16,
		itemWidth = 16;
};

#endif