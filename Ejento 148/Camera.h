#ifndef _Camera_HPP
#define _Camera_HPP

#include "player.h"

class Camera
{
public:
	Camera(Player & player, int levelWidth);
	void Reset(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
	sf::Vector2f getPosition() { return cameraPosition; }

private:
	sf::View view;
	Player & player;
	sf::Vector2f screenDimensions;
	sf::Vector2f cameraPosition;
	int levelWidth;
};

#endif