#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "ScoreScreen.h"
#include <iostream>
#include "score.h"
#include <sstream>
#include <istream>
#include <string>

ScoreScreen::ScoreScreen() {
	font.loadFromFile("resources/fonts/DKFaceYourFears.ttf");
	text.setFont(font);
}

void ScoreScreen::draw(sf::RenderWindow &window) {
	window.clear();

	text.setPosition(sf::Vector2f(300, 50));
	text.setString("Highscores");
	text.setCharacterSize(50);
	window.draw(text);
	
	std::vector<std::string> scorevec = score.getScores();
	std::vector<std::string> parts;

	for (auto i : scorevec) {
		std::stringstream test(i);
		std::string segment;

		while (std::getline(test, segment, ' '))
		{
			parts.push_back(segment);
		}
	}

	for (auto i : parts) {

		if (x > 2) {
			x = 0;
			y++;
		}

		std::cout << i << "\n";
		text.setPosition(sf::Vector2f(300 + (100 * x), 120 + (50 * y)));
		text.setString(i);
		text.setCharacterSize(20);
		window.draw(text);
		x++;
	}	
	window.display();
}