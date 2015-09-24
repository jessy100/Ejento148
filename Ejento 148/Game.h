#ifndef _GAME_HPP
#define _GAME_HPP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Game
{

public:
	static void Start();
private:
	static bool IsExiting();
	static void GameLoop();
	static void ShowSplashScreen();
	static void ShowMenu();
	static void ExitGame();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
};

#endif