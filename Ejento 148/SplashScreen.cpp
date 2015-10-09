#include "stdafx.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow &window) {
	sf::Texture texture;
	if (!(texture.loadFromFile("resources/images/SplashScreen.png"))) { return; }

	sf::Sprite sprite;
	sprite.setTexture(texture);

	window.draw(sprite);
	window.display();

	sf::Event event;
	while (true) {
		while (window.waitEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed || 
				event.type == sf::Event::EventType::MouseButtonPressed || 
				event.type == sf::Event::EventType::Closed) {
				return;
			}
		}
	}
}