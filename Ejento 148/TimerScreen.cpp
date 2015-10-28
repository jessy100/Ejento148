#include <SFML\Graphics.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include <SFML\System\Clock.hpp>
#include "TimerScreen.h"

timerScreen::timerScreen(sf::Vector2f position): 
	position{position}
{}

void timerScreen::draw(sf::RenderWindow & window) {
	sf::Font font;
	if (!font.loadFromFile("DKFaceYourFears.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}



	std::ostringstream os;
	os << "time: " << min << ":" << sec << ":" << imsec;
	std::string s = os.str();


	sf::Text timerScreen;
	timerScreen.setPosition(position);
	timerScreen.setFont(font);
	timerScreen.setString(s);
	timerScreen.setCharacterSize(30);
	window.draw(timerScreen);
}

void timerScreen::timer() {
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