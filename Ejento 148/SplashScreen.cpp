#include "stdafx.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow &renderWindow) {
	sf::Texture texture;
	if (!(texture.loadFromFile("resources/images/SplashScreen.png"))) { return; }

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(0.5, 0.5);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true) {
		while (renderWindow.waitEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed) {
				return;
			}
		}
	}
}