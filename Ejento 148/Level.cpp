#include "stdafx.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

void Level::Load() {
	std::ifstream levelMap("resources/levels/level1.txt");

	if (levelMap.is_open()) {
		std::string tileLocation;
		levelMap >> tileLocation;
		tileTexture.loadFromFile(tileLocation);
		tiles.setTexture(tileTexture);
		while (!levelMap.eof()) {
			std::string str;
			levelMap >> str;

			// x is character before comma, 2 is character after comma
			char x = str[0], y = str[2];

			// Check if found characters are digits. If not, set to -1 -1 to ignore when drawing.
			// Use x - '0' to prevent conversion to ascii
			if (!isdigit(x) || !isdigit(y)) {
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
			} else {
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');
			}

			// Check if next character is new line if true, increment y counter, if not increment x counter.
			if (levelMap.peek() == '\n') {
				loadCounter.x = 0;
				loadCounter.y++;
			}else {
				loadCounter.x++;
			}
		}
		loadCounter.y++;
	}

	levelMap.close();
}


void Level::Show(sf::RenderWindow &window) {
	Player player(sf::Vector2f(100, 100), "Steve", 200.0, 3);
	Enemy enemy(sf::Vector2f(300, 100), 100.0, 3);

	while (playingLevel) {
		window.clear(sf::Color(255, 255, 255)); // White background
		
		for (int i = 0; i < loadCounter.x; ++i) {
			for (int j = 0; j < loadCounter.y; ++j) {
				if (map[i][j].x != -1 && map[i][j].y != -1) {
					tiles.setPosition(i * tileSize, j * tileSize);
					tiles.setTextureRect(sf::IntRect(map[i][j].x * tileSize,
						map[i][j].y * tileSize,
						tileSize,
						tileSize));

					player.CheckCollision(sf::IntRect(i * tileSize,
						j * tileSize,
						tileSize,
						tileSize));

					enemy.CheckCollision(sf::IntRect(i * tileSize,
						j * tileSize,
						tileSize,
						tileSize));

					window.draw(tiles);
				}
			}
		}
		
		enemy.update(window);
		player.update(window);
		window.display();
	}
}

void Level::SetPlayingLevel(bool p) { playingLevel = p; }