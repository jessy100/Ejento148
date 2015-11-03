#include "stdafx.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Tile.h"
#include "InteractiveTile.h"
#include "BackgroundTile.h"
#include "TimerCounter.h"
#include "ScoreCounter.h"
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
			
			std::string posX,posY = "";

			// x is character before comma, 2 is character after comma
			char x = str[0], y = str[2]; 
			if (str[3] != NULL) {
				 
			}
			
			

			// Use x - '0' to prevent conversion to ascii		
			if (isdigit(x) || isdigit(y)) {
				if ((y - '0') > 5) {
					posX = std::to_string(str[4] - '0') + std::to_string(str[5] - '0') + std::to_string(str[6] - '0');
					posY = std::to_string(str[8] - '0') + std::to_string(str[9] - '0') + std::to_string(str[10] - '0');
					
					// create new interactive tile
					tileVec.push_back(new InteractiveTile(sf::Vector2f(atoi(posX.c_str()),
						atoi(posY.c_str())), tileLocation, sf::Vector2f(x - '0', y - '0')));
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
	
	Player player(sf::Vector2f(100, 500), "Ejento 148", 10);
	
	timerCounter timer(sf::Vector2f(50,50));
	scoreCounter score(sf::Vector2f(400,50));
	score.add(20);

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

	Enemy enemy1(sf::Vector2f(100, 200), 100.0f, 3);
	Enemy enemy2(sf::Vector2f(200, 200), 100.0f, 3);
	Enemy enemy3(sf::Vector2f(300, 200), 100.0f, 3);
	Enemy enemy4(sf::Vector2f(400, 200), 100.0f, 3);
	enemies.push_back(enemy1);
	//enemies.push_back(enemy2);
	//enemies.push_back(enemy3);
	//enemies.push_back(enemy4);

	Camera camera(player);

	while (playingLevel) {
		window.clear(sf::Color(255, 255, 255)); // White background

		for (auto& tile : tileVec) {
			tile->draw(window);

			if (tile->getType() == "InteractiveTile") {
				//std::cout << player.getPlayerRect().top << "\n";
				sf::IntRect tileRect = tile->getRect();
				//std::cout << tileRect.left << " | " << tileRect.width << "\n";
				if (tileRect.intersects(player.getPlayerRect())) {
					player.CheckCollision(tileRect);
				}
				
			}
		}

		// Loop through all items in the items vector and check if they collide with the player
		for (std::vector<int>::size_type i = 0; i != enemies.size(); i++) {
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
		timer.draw(window,camera.getPosition());
		score.draw(window, camera.getPosition());
		window.display();
	}
}

void Level::SetPlayingLevel(bool p) { playingLevel = p; }