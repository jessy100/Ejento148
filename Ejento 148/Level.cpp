#include "stdafx.h"
#include "Level.h"
#include "Player.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

void Level::Load() {
	std::ifstream openFile("resources/levels/level1.txt");

	if (openFile.is_open()) {
		std::string tileLocation;
		openFile >> tileLocation;
		tileTexture.loadFromFile(tileLocation);
		tiles.setTexture(tileTexture);
		while (!openFile.eof()) {
			std::string str;
			openFile >> str;

			// x is character before comma, 2 is character after comma
			char x = str[0], y = str[2];

			// Check if found characters are digits. If not, set to -1 -1 to ignore when drawing.
			// Use x - '0' to prevent conversion to ascii
			if (!isdigit(x) || !isdigit(y))
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
			else
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');

			// Check if next character is new line if true, increment y counter, if not increment x counter.
			if (openFile.peek() == '\n') {
				loadCounter.x = 0;
				loadCounter.y++;
			}else {
				loadCounter.x++;
			}
		}
		loadCounter.y++;
	}
}


void Level::Show(sf::RenderWindow &window) {
	Player player(sf::Vector2f(100, 100), "Steve",
		80.0, 3); // Only for test, remove this

	while (playingLevel) {
		window.clear();
		
		for (int i = 0; i < loadCounter.x; i++) {
			for (int j = 0; j < loadCounter.y; j++) {
				if (map[i][j].x != -1 && map[i][j].y != -1) {
					
					tiles.setPosition(i * 32, j * 32);
					tiles.setTextureRect(sf::IntRect(map[i][j].x * 32, map[i][j].y * 32, 32, 32));				
					player.CheckCollision(sf::IntRect(i * 32, j * 32, 32, 32));

					window.draw(tiles);
				}
			}
		}
		
		player.update(window);
		window.display();
	}
}

void Level::setPlayingLevel(bool p) { playingLevel = p; }