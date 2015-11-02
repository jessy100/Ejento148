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
	MenuResult Show(sf::RenderWindow& window);
private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> menuItems;
};

#endif