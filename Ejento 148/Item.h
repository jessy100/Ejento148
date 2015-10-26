#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <SFML/Graphics.hpp>

class Item {
public:
	Item(sf::Vector2f, std::string n, int l);


	void CheckCollision(sf::IntRect);
	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position, velocity = sf::Vector2f(0, 0);
	sf::IntRect itemRect;
	std::string effect;

	const float gravity = 10.0f;
	int lives,
		itemHeight = 32,
		itemWidth = 32;
	bool grounded = false;
};

#endif