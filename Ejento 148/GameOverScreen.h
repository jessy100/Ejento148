#pragma once
#ifndef _GAMEOVERSCREEN_HPP
#define _GAMEOVERSCREEN_HPP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "WebScore.h"

class GameOverScreen {
public:


	GameOverScreen();
	void draw(sf::RenderWindow &window);
private:
	WebScore score;
	sf::Font font;
	sf::Text text;
	std::string name = "";
	bool isDone = false;
};

#endif