#include "player.h"

class camera
{
public:
	camera(Player & player);
	
	void update(sf::RenderWindow &window);

private:
	sf::View view;
	Player & player;
	sf::Vector2f screenDimensions;
	sf::Vector2f cameraPosition;
};

