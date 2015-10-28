
#include "ScoreCounter.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

scoreCounter::scoreCounter(sf::Vector2f position, int beginScore) :
	position{position},
	curScore{beginScore}
{}

void scoreCounter::draw(sf::RenderWindow & window)  {
	sf::Font font;
	if (!font.loadFromFile("DKFaceYourFears.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	std::string scoreString = std::to_string(curScore);


	sf::Text scoreScreen;
	scoreScreen.setPosition(position);
	scoreScreen.setFont(font);
	scoreScreen.setString("Score: " + scoreString);
	scoreScreen.setCharacterSize(30);
	window.draw(scoreScreen);
}

void scoreCounter::add(int score) {
	curScore = curScore + score;
}

void scoreCounter::lower(int score) {
	curScore = curScore - score;
}