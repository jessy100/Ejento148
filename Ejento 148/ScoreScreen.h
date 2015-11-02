#ifndef _SCORESCREEN_HPP
#define _SCORESCREEN_HPP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "score.h"

class ScoreScreen {
public:
	
	
	ScoreScreen();
	void draw(sf::RenderWindow &window);
private:
	Score score;
	sf::Font font;
	sf::Text text;
	int x,y = 0;
};

#endif