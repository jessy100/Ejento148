#ifndef _LEVEL_HPP
#define _LEVEL_HPP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Tile.h"
#include "Game.h"

class Level {
public:
	void Show(sf::RenderWindow& window, Game *game);
	void Load();
	void GameOver();
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