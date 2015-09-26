#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Player.h"
#include "Level.h"

void Game::Start(void) {
	if (gameState != Uninitialized)
		return;

	window.create(sf::VideoMode(800, 600, 32), "Ejento 148");
	gameState = Game::ShowingSplash;
	window.setFramerateLimit(200);

	while (!IsExiting()) {
		GameLoop();
	}

	window.close();
}

void Game::ShowSplashScreen() {
	SplashScreen splashScreen;
	splashScreen.Show(window);
	gameState = Game::ShowingMenu;
}

void Game::ShowMenu() {
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(window);

	switch (result) {
		case MainMenu::Exit:
			gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			gameState = Game::Playing;
			break;
	}
}

void Game::ExitGame() { exit(0); }

bool Game::IsExiting() {
	if (gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::PlayLevel() {
	Level level;
	level.Load();
	level.Show(window);
}

void Game::GameLoop() {
	sf::Event currentEvent;
	while (window.waitEvent(currentEvent)) {
		switch (gameState) {
			case Game::ShowingMenu: {
				ShowMenu();
				
				break;
			}
			case Game::ShowingSplash: {
				ShowSplashScreen();
				break;
			}
			case Game::Exiting: {
				ExitGame();
				break;
			}
			case Game::Playing: {
				PlayLevel();
				break;
			}
		}
	}
}

Game::GameState Game::gameState = Uninitialized;
sf::RenderWindow Game::window;