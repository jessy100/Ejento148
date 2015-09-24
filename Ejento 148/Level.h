#ifndef _LEVEL_HPP
#define _LEVEL_HPP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Level {
public:
	void Show(sf::RenderWindow& window);

	void setPlayingLevel(bool);
private:
	bool playingLevel = true;
};

#endif