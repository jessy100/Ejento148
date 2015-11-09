/*!
*   @author     Aydin Biber
*   @project    Themaopdracht 5, Ejento 148
*   @brief     The code to show the main menu.
*/

#ifndef _MAINMENU_HPP
#define _MAINMENU_HPP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <list>

class MainMenu {
public:
	enum class MenuResult { Nothing, Exit, Play, ScoreBoard };
	
	struct MenuItem {
		public:
			sf::Rect<int> rect;
			MenuResult action;
		};

	/**
	* \brief the show method draws the Menu to the window.
	* \param RenderWindow the window to draw on.
	*/
	MenuResult Show(sf::RenderWindow& window);
private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> menuItems;
};

#endif