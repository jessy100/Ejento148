#include <SFML\Graphics.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include <SFML\System\Clock.hpp>
#include "TimerCounter.h"

TimerCounter::TimerCounter(sf::Vector2f position) :
	position{ position }
{
	font.loadFromFile("resources/fonts/DKFaceYourFears.ttf");
	text.setFont(font);
}

void TimerCounter::draw(sf::RenderWindow & window, sf::Vector2f position) {
	timer();

	std::ostringstream os;
	os << "time: " << min << ":" << sec << ":" << imsec;
	std::string s = os.str();

	text.setPosition(position);
	text.setString(s);
	text.setCharacterSize(25);
	window.draw(text);
}

void TimerCounter::timer() {
	sf::Time msec = clock.getElapsedTime();
	imsec = msec.asMilliseconds();
	if (imsec >= 999) {
		imsec = 0;
		clock.restart();
		sec++;
	}
	if (sec == 59) {
		min++;
		sec = 0;
	}
}