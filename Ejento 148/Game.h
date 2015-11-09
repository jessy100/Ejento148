/*!
*   @author     Aydin Biber
*   @project    Themaopdracht 5, Ejento 148
*   @brief      The code that manages the gamestates and gameloop
*/

#ifndef _GAME_HPP
#define _GAME_HPP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Audio.h"
#include "GameOverScreen.h"

class Game {
public:
	/** \brief Starts the game
	* \details Creates the renderWindow and initializes the gamestate
	*/
	void Start();
	/** \brief Shows the game over screen
	*/
	void ShowGameOverScreen();
private:
	bool IsExiting();
	
	/** \brief Checks what the current state is and runs it
	*/
	void GameLoop();

	/** \brief Shows the splashScreen
	*/
	void ShowSplashScreen();

	/** \brief Shows the menu and checks which menu item is clicked
	*/
	void ShowMenu();
	
	/** \brief Closes the sf::renderWindow
	*/
	void ExitGame();

	/** \brief Loads the level and starts the level loop
	*/
	void PlayLevel();

	/** \brief Shows the scoreboard
	*/
	void ShowScoreboard();


	enum class GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting, ShowingScoreboard, ShowingGameOverScreen
	};

	GameState gameState = GameState::Uninitialized;
	sf::RenderWindow window;

	int screenWidth = 896, screenHeight = 640, screenDepth = 32;

};

#endif