#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "AnimatedSprite.h"

class Player {
public:
	Player(sf::Vector2f, std::string n, float s, int l);

	std::string getName();
	void setName(std::string);
	float getSpeed();
	void setSpeed(float);
	int getLives();
	void setLives(int);
	void Player::setAnimation(Animation &);
	void Player::gravity();
	bool CheckCollision(sf::FloatRect collider);

	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	std::string name;
	float speed;
	int lives;
	Animation *currentAnimation;
	Animation walkingAnimationDown;
	Animation walkingAnimationLeft;
	Animation walkingAnimationRight;
	Animation walkingAnimationUp;
	AnimatedSprite animation;
	bool noKeyWasPressed = true;
	sf::Clock frameClock;
};

#endif