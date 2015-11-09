/*!
*   @author     Kevin Damen
*   @project    Themaopdracht 5, Ejento 148
*   @brief     The code to show the score counter.
*/

#ifndef _SCORECOUNTER_HPP
#define _SCORECOUNTER_HPP

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include "ScoreCounter.h"

class ScoreCounter {
public:
	/**
	*\brief this is the constructor for the scoreCounter class.
	*\details initialises the scoreCounter class.
	*\param position the position of the score counter.
	*\param beginscore the start score.
	*/
	ScoreCounter(sf::Vector2f position, int beginScore = 0);

	/** \brief Draws the ScoreCounter
	* \details Draws the ScoreCounter on the sf::RenderWindow it gets by reference.
	* \param window the sf::RenderWindow reference.
	* \param position the position of the scorecounter.
	*/
	static void draw(sf::RenderWindow & window, sf::Vector2f position);

	/** \brief increases the score
	* \details increases the score by its amount in the parameter.
	* \param score the amount of points you want to add.
	*/
	static void increase(int score);

	/** \brief decrease the score
	* \details decrease the score by its amount in the parameter.
	* \param score the amount of points you want to deduct.
	*/
	static void decrease(int score);

private:
	static sf::Vector2f position;
	static int curScore;
	static sf::Font font;
	static sf::Text text;
};

#endif 