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
	playButton.rect.top = 145;
	playButton.rect.left = 0;
	playButton.rect.width = 1023;
	playButton.rect.height = 235;
	playButton.action = Play;

	// Exit menu item
	MenuItem exitButton;
	playButton.rect.top = 383;
	playButton.rect.left = 0;
	playButton.rect.width = 1023;
	playButton.rect.height = 235;
	playButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y) {
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++) {
		sf::Rect<int> menuItemRect = (*it).rect;
		if (x > menuItemRect.left && x < menuItemRect.left + menuItemRect.width && y > menuItemRect.top && y < menuItemRect.height + menuItemRect.top) {
			return (*it).action;
		}
	}

	return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow &window) {
	sf::Event menuEvent;

	while (true) {
		while (window.waitEvent(menuEvent)) {
			if (menuEvent.type == sf::Event::MouseButtonPressed) {
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}

			if (menuEvent.type == sf::Event::Closed) {
				return Exit;
			}
		}
	}
}