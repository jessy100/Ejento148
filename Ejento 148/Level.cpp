#include "stdafx.h"
#include "Level.h"
#include "Player.h"

void Level::Show(sf::RenderWindow &window) {
	Player player(sf::Vector2f(0, 0), "Steve",
		80.0, 3); // Only for test, remove this

	//sf::Event currentEvent;
	while (playingLevel) {
		window.clear();
		player.update(window);
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

void Level::setPlayingLevel(bool p) { playingLevel = p; }