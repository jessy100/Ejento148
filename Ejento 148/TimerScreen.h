#pragma once
#ifndef _TIMERSCREEN_HPP
#define _TIMERSCREEN_HPP

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

class timerScreen {
public:
	/*
	constructor for the timerscreen class.
	you give a position to the constructor. 
	for the place where the timer will be standing on the play window.
	*/
	timerScreen(sf::Vector2f position);

	/*
	the draw methode draws the timer to the window.
	with it's currect values. when the values change you have to draw it again. 
	you give a window to the draw methode to let it know in which window you want to draw. 
	*/
	void draw(sf::RenderWindow & window);

	/*
	in the timer methode will the timer be operated. 
	without this methode the timer won't work. 
	*/
	void timer();

private:
	sf::Vector2f position;
	sf::Clock clock; 
	int min = 0;
	int sec = 0;
	int imsec  = 0;
};


#endif 