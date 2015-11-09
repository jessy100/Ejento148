/*!
*   @author     Kevin Damen
*   @project    Themaopdracht 5, Ejento 148
*   @brief     The code to show the time counter.
*/

#ifndef _TIMERCOUNTER_HPP
#define _TIMERCOUNTER_HPP

#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

class TimerCounter {
public:
	/**
	* \brief constructor for the TimerCounter class.
	* \details initialises the TimerCounter class
	* \param position for the place where the timer will be standing on the play window.
	*/
	TimerCounter(sf::Vector2f position);

	/**
	* \brief the draw method draws the timer to the window.
	* \details draw the timer to the window with it's currect values. when the values change you have to draw it again.
	* \param RenderWindow the window to draw on.
	* \param position the position where the timer is drawn.
	*/
	void draw(sf::RenderWindow & window, sf::Vector2f position);

	/*
	* \brief The actual timer.
	* \details starts the clock and updates it.
	*/
	void timer();

private:
	sf::Vector2f position;
	sf::Clock clock;
	int min = 0;
	int sec = 0;
	int imsec = 0;
	sf::Font font;
	sf::Text text;
};


#endif 