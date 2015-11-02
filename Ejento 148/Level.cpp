#include "stdafx.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Tile.h"
#include "InteractiveTile.h"
#include "BackgroundTile.h"
#include <vector>
#include "Camera.h"
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

		while (!levelMap.eof()) {
			std::string str;
			levelMap >> str;

			// x is character before comma, 2 is character after comma
			char x = str[0], y = str[2];

			// Use x - '0' to prevent conversion to ascii		
			if (isdigit(x) || isdigit(y)) {
				if ((x - '0') > 5) {
					// create new interactive tile
					tileVec.push_back(new InteractiveTile(sf::Vector2f(loadCounter.x * 128,
						loadCounter.y * 128), tileLocation, sf::Vector2f(x - '0', y - '0')));
				} else {
					//create background tile
					tileVec.push_back(new BackgroundTile(sf::Vector2f(loadCounter.x * 128,
						loadCounter.y * 128), tileLocation, sf::Vector2f(x - '0', y - '0')));
				}
			}

			// Check if next character is new line if true, increment y counter, if not increment x counter.
			if (levelMap.peek() == '\n') {
				loadCounter.x = 0;
				loadCounter.y++;
			} else {
				loadCounter.x++;
			}
		}
		loadCounter.y++;
	}

	levelMap.close();
}


void Level::Show(sf::RenderWindow &window) {
	Player player(sf::Vector2f(100, 500), "Ejento 148", 3);

	std::vector<Item> items;
	std::vector<Enemy> enemies;

	Item item1(sf::Vector2f(100, 500), "health");
	Item item2(sf::Vector2f(200, 500), "damage");
	Item item3(sf::Vector2f(300, 500), "health");
	Item item4(sf::Vector2f(400, 500), "damage");
	items.push_back(item1);
	items.push_back(item2);
	items.push_back(item3);
	items.push_back(item4);

	Enemy enemy1(sf::Vector2f(100, 200), 200.0f, 3);
	Enemy enemy2(sf::Vector2f(200, 200), 200.0f, 3);
	Enemy enemy3(sf::Vector2f(300, 200), 200.0f, 3);
	Enemy enemy4(sf::Vector2f(400, 200), 200.0f, 3);
	enemies.push_back(enemy1);
	enemies.push_back(enemy2);
	enemies.push_back(enemy3);
	enemies.push_back(enemy4);

	Camera camera(player);

	while (playingLevel) {
		window.clear(sf::Color(255, 255, 255)); // White background

		for (auto& tile : tileVec) {
			tile->draw(window);
		}

		// Loop through all items in the items vector and check if they collide with the player
		for (std::vector<int>::size_type i = 0; i != enemies.size(); ++i) {
			if (!enemies[i].isKilled()) {
				enemies[i].update(window);
				enemies[i].CheckCollision(player);
			}
		}

		// Loop through all items in the items vector and check if they collide with the player
		for (std::vector<int>::size_type i = 0; i != items.size(); ++i) {
			if (!items[i].isLooted()) {
				items[i].draw(window);
				items[i].CheckCollision(player);
			}
		}

		//enemy.update(window);
		player.update(window);
		camera.update(window);
		window.display();
	}
}

void Level::SetPlayingLevel(bool p) { playingLevel = p; }