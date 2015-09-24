#include "stdafx.h"
#include "Level.h"
#include "Player.h"

void Level::Show(sf::RenderWindow &window) {
	Player player(sf::Vector2f(0, 0), "Steve",
		10.0, 3); // Only for test, remove this

	sf::Event currentEvent;
	while (window.waitEvent(currentEvent)) {
		window.clear(sf::Color(0, 0, 0));
		player.draw(window); // Only for test, remove this
		window.display();

		/*if (currentEvent.type == sf::Event::Closed) {
			_gameState = Game::Exiting;
		}
		if (currentEvent.type == sf::Event::KeyPressed) {
			if (currentEvent.key.code == sf::Keyboard::Escape) {
				ShowMenu();
			}
		}*/
	}
}