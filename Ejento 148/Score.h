#ifndef _SCORE_HPP
#define _SCORE_HPP

#include <SFML\Graphics.hpp>
#include <string>
#include <http.h>
#include <SFML\Network.hpp>
#include "SFML\Network\Http.hpp"


class Score {
public:
	Score();


	void Score::getScores();
	void Score::saveScore(std::string name, std::string score, std::string tijd);
	void Score::parseResponseString(std::string str);
	void Score::draw(sf::RenderWindow &window);
private:
	sf::Http http;

};

#endif