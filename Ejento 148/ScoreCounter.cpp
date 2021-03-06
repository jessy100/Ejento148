#include "ScoreCounter.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

ScoreCounter::ScoreCounter(sf::Vector2f pos, int bs) {
	position = pos;
	curScore = bs;

	font.loadFromFile("resources/fonts/DKFaceYourFears.ttf");
	text.setFont(font);
}

void ScoreCounter::draw(sf::RenderWindow & window, sf::Vector2f position) {
	std::string scoreString = std::to_string(curScore);
	text.setPosition(position + sf::Vector2f(730,0));
	text.setString("Score: " + scoreString);
	text.setCharacterSize(30);
	window.draw(text);
}

void ScoreCounter::increase(int score) {
	curScore = curScore + score;
}

void ScoreCounter::decrease(int score) {
	curScore = curScore - score;
}

sf::Vector2f ScoreCounter::position;
int ScoreCounter::curScore;
sf::Font ScoreCounter::font;
sf::Text ScoreCounter::text;