#include "stdafx.h"
#include "Camera.h"


Camera::Camera(Player & player, int levelWidth) :
	player{ player },
	levelWidth{levelWidth}
{
	screenDimensions = sf::Vector2f(896, 640);
	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
}

void Camera::Reset(sf::RenderWindow &window) {
	view.reset(sf::FloatRect(0,0, screenDimensions.x, screenDimensions.y));
	window.setView(view);
}

void Camera::update(sf::RenderWindow &window) {
	cameraPosition.x = player.getPosition().x - (screenDimensions.x / 2);

	if (cameraPosition.x < 0) {
		cameraPosition.x = 0;
	}
	if (cameraPosition.x > (levelWidth - screenDimensions.x)) {
		cameraPosition.x = levelWidth - screenDimensions.x;
	}
	view.reset(sf::FloatRect(cameraPosition.x, cameraPosition.y, screenDimensions.x, screenDimensions.y));
	window.setView(view);
}