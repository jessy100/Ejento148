#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "GameOverScreen.h"
#include <iostream>
#include "WebScore.h"
#include <sstream>
#include <istream>
#include <string>

GameOverScreen::GameOverScreen() {
	font.loadFromFile("resources/fonts/DKFaceYourFears.ttf");
	text.setFont(font);
	name = "";
}

GameOverScreen & GameOverScreen::getInstance() {
	static GameOverScreen instance;
	return instance;
}

void GameOverScreen::draw(sf::RenderWindow &window) {

	window.clear();

	text.setPosition(sf::Vector2f(300, 50));
	text.setString("Game Over");
	text.setCharacterSize(50);
	window.draw(text);

	text.setPosition(sf::Vector2f(310, 130));
	text.setString("Enter your name");
	text.setCharacterSize(30);
	window.draw(text);

	sf::Event event;
	while (window.pollEvent(event)) {
		if (!isDone) {
			if (event.type == sf::Event::TextEntered) {	
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					isDone = true;
					std::cout << "isDone";
					score.saveScore(name, "50", "1:30");
				}
				else {
					name += event.text.unicode;
				}
			}
		}
	}

	text.setPosition(sf::Vector2f(340, 210));
	text.setString(name);
	text.setCharacterSize(20);
	window.draw(text);
	window.display();
	
}