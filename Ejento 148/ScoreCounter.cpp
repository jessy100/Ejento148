#include "ScoreCounter.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

scoreCounter::scoreCounter(sf::Vector2f position, int beginScore) :
	position{ position },
	curScore{ beginScore }
{
	font.loadFromFile("resources/fonts/DKFaceYourFears.ttf");
	text.setFont(font);
}

void scoreCounter::draw(sf::RenderWindow & window, sf::Vector2f position) {
	
	std::string scoreString = std::to_string(curScore);

	text.setPosition(position + sf::Vector2f(730,0));
	text.setString("Score: " + scoreString);
	text.setCharacterSize(30);
	window.draw(text);
}

void scoreCounter::add(int score) {
	curScore = curScore + score;
}

void scoreCounter::lower(int score) {
	curScore = curScore - score;
}