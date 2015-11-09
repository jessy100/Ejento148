/*!
*   @author     Jessy Visch
*   @project    Themaopdracht 5, Ejento 148
*   @brief      the code to load, draw & handle all events in a level.
*/

#ifndef _LEVEL_HPP
#define _LEVEL_HPP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Tile.h"
#include "Game.h"
#include "Camera.h"

class Level {
public:

	/**
	* \brief the show method draws the splash to the window.
	* \details show draws the splashscreen to the window
	* \param RenderWindow the window to draw on.
	*/
	void Show(sf::RenderWindow& window, Game *game);
	void Load();
	void GameOver(Game *game, Camera &camera, sf::RenderWindow &window);
	void SetPlayingLevel(bool);
private:
	bool playingLevel = true;
	float tileSize = 128;
	sf::Vector2i loadCounter = sf::Vector2i(0, 0);
	sf::Vector2i map[200][200];
	sf::Texture tileTexture;
	sf::Sprite tiles;
	std::vector<Tile *> tileVec;
	int levelWidth;
};

#endif