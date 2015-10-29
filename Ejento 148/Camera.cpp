#include "stdafx.h"
#include "Camera.h"


Camera::Camera(Player & player) :
	player{ player }
{
	screenDimensions = sf::Vector2f(896, 640);
	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
}


void Camera::update(sf::RenderWindow &window) {
	cameraPosition.x = player.getPosition().x - (screenDimensions.x / 2);

	if (cameraPosition.x < 0) {
		cameraPosition.x = 0;
	}
	view.reset(sf::FloatRect(cameraPosition.x, cameraPosition.y, screenDimensions.x, screenDimensions.y));
	window.setView(view);
}