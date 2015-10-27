#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Player.h"
#include "Level.h"
#include "Audio.h"

void Game::Start(void) {
	window.create(
		sf::VideoMode( 
			screenHeight,
			screenWidth, 
			screenDepth
		), 
		"Ejento 148"
	);

	gameState = GameState::ShowingSplash;
	window.setFramerateLimit(200);

	while (!IsExiting()) { GameLoop(); }

	window.close();
}

void Game::ShowSplashScreen() {
	SplashScreen splashScreen;
	splashScreen.Show(window);
	gameState = GameState::ShowingMenu;
}

void Game::ShowMenu() {
	audio.MusicStart("menu-music.mp3", 4);
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(window);

	switch (result) {
		case MainMenu::MenuResult::Exit:
			gameState = GameState::Exiting;
			break;
		case MainMenu::MenuResult::Play:
			gameState = GameState::Playing;
			break;
	}
}

void Game::ExitGame() { exit(0); }

bool Game::IsExiting() {
	if (gameState == GameState::Exiting) {
		return true;
	} else {
		return false;
	}
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
			case GameState::ShowingMenu: {
				ShowMenu();
				break;
			}
			case GameState::ShowingSplash: {
				ShowSplashScreen();
				break;
			}
			case GameState::Exiting: {
				ExitGame();
				break;
			}
			case GameState::Playing: {
				PlayLevel();
				break;
			}
		}
	}
}
