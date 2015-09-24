#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Player.h"
#include "Level.h"

void Game::Start(void) {
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Ejento 148");
	_gameState = Game::ShowingSplash;

	while (!IsExiting()) {
		GameLoop();
	}

	_mainWindow.close();
}

void Game::ShowSplashScreen() {
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu() {
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);

	switch (result) {
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			break;
	}
}

void Game::ExitGame() { exit(0); }

bool Game::IsExiting() {
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::PlayLevel() {
	Level level;
	level.Show(_mainWindow);
}

void Game::GameLoop() {
	sf::Event currentEvent;
	while (_mainWindow.waitEvent(currentEvent)) {
		switch (_gameState) {
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

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;