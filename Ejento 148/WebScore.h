#ifndef _SCORE_HPP
#define _SCORE_HPP

#include <SFML\Graphics.hpp>
#include <string>
#include <http.h>
#include <SFML\Network.hpp>
#include "SFML\Network\Http.hpp"


class WebScore {
public:
	WebScore();

	std::vector<std::string> WebScore::getScores();
	void WebScore::saveScore(std::string name, std::string score, std::string tijd);
	void WebScore::parseResponseString(std::string str);
	void WebScore::draw(sf::RenderWindow &window);
private:
	sf::Http http;
	std::string segment;
	std::vector<std::string> seglist;

};

#endif