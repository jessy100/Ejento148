#pragma once
#ifndef _SCORECOUNTER_HPP
#define _SCORECOUNTER_HPP

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>


class scoreCounter {
public:
	/*
	this is the constructor for the scoreCounter class.
	you give the position and the beginScore to the constructor.
	the position is the place where the score will be on the window.
	the beginScore will be the score that will be showed when the windows is opened.
	*/
	scoreCounter(sf::Vector2f position, int beginScore = 0);

	/*
	the draw methode draws the score to the window.
	with it's currect values. when the values change you have to draw it again.
	you give a window to the draw methode to let it know in which window you want to draw.
	*/
	void draw(sf::RenderWindow & window, sf::Vector2f position);

	/*
	the add methode adds the score.
	you give a score to the methode. which is the value of the increase of the current score.
	*/
	void add(int score);

	/*
	the lower methode lowers the score.
	you give a score to the methode. which is the value of the decrease of the current score.
	*/
	void lower(int score);

private:
	sf::Vector2f position;
	int curScore;
	sf::Font font;
	sf::Text text;
};

#endif 