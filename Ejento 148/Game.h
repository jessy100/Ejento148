#ifndef _GAME_HPP
#define _GAME_HPP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Audio.h"

class Game {
public:
	void Start();
private:
	bool IsExiting();
	void GameLoop();
	void ShowSplashScreen();
	void ShowMenu();
	void ExitGame();
	void PlayLevel();

	enum class GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

	GameState gameState = GameState::Uninitialized;
	sf::RenderWindow window;

	int screenHeight = 640, screenWidth = 896, screenDepth = 32;
};

#endif