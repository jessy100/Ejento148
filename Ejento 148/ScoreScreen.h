/*!
*   @author     Jessy Visch
*   @project    Themaopdracht 5, Ejento 148
*   @brief      The code for showing the leaderboards
*/

#ifndef _SCORESCREEN_HPP
#define _SCORESCREEN_HPP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "WebScore.h"

class ScoreScreen {
public:
	
	/** \brief Constructor ScoreScreen.
	* \details Creates ScoreScreen instance.
	*/
	ScoreScreen();

	/** \brief Draws the ScoreScreen
	* \details Draws the ScoreSCreen on the sf::RenderWindow it gets by reference.
	* \param window the sf::RenderWindow reference.
	*/
	void draw(sf::RenderWindow &window);
private:
	WebScore score;
	sf::Font font;
	sf::Text text;
	int x,y = 0;
};

#endif