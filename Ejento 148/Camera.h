#include "player.h"

class Camera
{
public:
	Camera(Player & player);

	void update(sf::RenderWindow &window);

private:
	sf::View view;
	Player & player;
	sf::Vector2f screenDimensions;
	sf::Vector2f cameraPosition;
};
