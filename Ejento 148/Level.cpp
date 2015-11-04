#include "stdafx.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Tile.h"
#include "Game.h"
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

			std::string posX, posY = "";

			// x is character before comma, 2 is character after comma
			char x = str[0], y = str[2];

			// Use x - '0' to prevent conversion to ascii		
			if (isdigit(x) || isdigit(y)) {
				if ((y - '0') > 5) {
					posX = std::to_string(str[4] - '0') + std::to_string(str[5] - '0') + std::to_string(str[6] - '0') + std::to_string(str[7] - '0');
					posY = std::to_string(str[9] - '0') + std::to_string(str[10] - '0') + std::to_string(str[11] - '0');

					// create new interactive tile
					tileVec.push_back(new InteractiveTile(sf::Vector2f(atoi(posX.c_str()),
						atoi(posY.c_str())), tileLocation, sf::Vector2f(x - '0', y - '0')));
				}
				else {
					//create background tile


					tileVec.push_back(new BackgroundTile(sf::Vector2f(loadCounter.x * tileSize,
						loadCounter.y * tileSize), tileLocation, sf::Vector2f(x - '0', y - '0')));
				}
			}

			// Check if next character is new line if true, increment y counter, if not increment x counter.
			if (levelMap.peek() == '\n') {
				if (loadCounter.x * tileSize >= levelWidth) {
					levelWidth = loadCounter.x * tileSize;
				}

				loadCounter.x = 0;
				loadCounter.y++;
			}
			else {
				loadCounter.x++;
			}
		}
		loadCounter.y++;
	}

	levelMap.close();
}


void Level::Show(sf::RenderWindow &window, Game *game) {

	sf::Event event;
	while (window.pollEvent(event)) {}

	Player player(sf::Vector2f(100, 500), "Ejento 148", 10);

	TimerCounter timer(sf::Vector2f(50, 50));
	ScoreCounter score(sf::Vector2f(400, 50));
	score.increase(20);

	std::vector<Item *> items;
	std::vector<Enemy *> enemies;

	/*
	Create new items and enemies
	*/
	items.push_back(new Item(sf::Vector2f(100, 500), "health"));
	items.push_back(new Item(sf::Vector2f(200, 500), "damage"));
	items.push_back(new Item(sf::Vector2f(300, 500), "health"));
	items.push_back(new Item(sf::Vector2f(400, 500), "damage"));

	enemies.push_back(new Enemy(sf::Vector2f(400, 570), 100.0f, 3));
	enemies.push_back(new Enemy(sf::Vector2f(1100, 570), 100.0f, 3));
	enemies.push_back(new Enemy(sf::Vector2f(1950, 570), 100.0f, 3));
	enemies.push_back(new Enemy(sf::Vector2f(2800, 570), 100.0f, 3));

	Camera camera(player,levelWidth);

	while (playingLevel) {
		window.clear(sf::Color(255, 255, 255)); // White background

		for (auto& tile : tileVec) {
			tile->draw(window);

			if (tile->getType() == "InteractiveTile") {
				sf::IntRect tileRect = tile->getRect();
				if (tileRect.intersects(player.getPlayerRect())) {
					player.CheckCollision(tileRect);
				}

			}
		}

		// Loop through all items in the items vector and check if they collide with the player
		for (std::vector<int>::size_type i = 0; i != enemies.size(); i++) {
			if (!enemies[i]->isKilled()) {
				enemies[i]->update(window, player);
				enemies[i]->CheckCollision(player);
			}
		}

		// Loop through all items in the items vector and check if they collide with the player
		for (std::vector<int>::size_type i = 0; i != items.size(); ++i) {
			if (!items[i]->isLooted()) {
				items[i]->draw(window);
				items[i]->CheckCollision(player);
			}
		}

		// Check if the player character is dead
		

		player.update(window);
		camera.update(window);
		timer.draw(window, camera.getPosition());
		score.draw(window, camera.getPosition());

		if (player.isDead() == true || player.getPosition().x > levelWidth) {
			GameOver(game, camera, window);
		}
		std::cout << player.getPosition().x << "\n";
		window.display();
	}
} 

//testcomment

void Level::GameOver(Game *game, Camera &camera, sf::RenderWindow &window) {
	// The player has died, and the game is over
	// Call the screen where the player can put in his name for the leaderboards
	playingLevel = false;
	game->ShowGameOverScreen();
	camera.Reset(window);
}

void Level::SetPlayingLevel(bool p) { playingLevel = p; }