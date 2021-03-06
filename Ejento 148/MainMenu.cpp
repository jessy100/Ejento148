#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow &window) {
	// Load menu image from file
	sf::Texture texture;
	texture.loadFromFile("resources/images/MainMenu.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);

	// Play menu item
	MenuItem playButton;
	playButton.rect.top = 0;
	playButton.rect.left = 200;
	playButton.rect.width = 800;
	playButton.rect.height = 215;
	playButton.action = MenuResult::Play;

	// Exit menu item
	MenuItem exitButton;
	exitButton.rect.top = 383;
	exitButton.rect.left = 200;
	exitButton.rect.width = 800;
	exitButton.rect.height = 235;
	exitButton.action = MenuResult::Exit;

	MenuItem leaderBoards;
	leaderBoards.rect.top = 216;
	leaderBoards.rect.left = 200;
	leaderBoards.rect.width = 800;
	leaderBoards.rect.height = 210;
	leaderBoards.action = MenuResult::ScoreBoard;


	menuItems.push_back(playButton);
	menuItems.push_back(exitButton);
	menuItems.push_back(leaderBoards);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y) {
	std::list<MenuItem>::iterator it;

	for (it = menuItems.begin(); it != menuItems.end(); it++) {
		sf::Rect<int> menuItemRect = (*it).rect;
		if (x > menuItemRect.left && x < menuItemRect.left 
			+ menuItemRect.width && y > menuItemRect.top 
			&& y < menuItemRect.height + menuItemRect.top)
		{
			return (*it).action;
		}
	}

	return MenuResult::Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow &window) {
	sf::Event menuEvent;

	while (true) {
		while (window.waitEvent(menuEvent)) {
			if (menuEvent.type == sf::Event::MouseButtonPressed) {
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}

			if (menuEvent.type == sf::Event::Closed) {
				return MenuResult::Exit;
			}
		}
	}
}