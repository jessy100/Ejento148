#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Score.h"
#include "SFML\Network\Http.hpp"


Score::Score() {
	http.setHost("http://jessy-visch.nl/");

}

std::vector<std::string> Score::getScores() {
	//Call the file index.php on host jessy-visch.nl/ejento
	sf::Http::Request request("ejento/index.php");

	//Sending the response and capturing the HTTP response
	sf::Http::Response response = http.sendRequest(request);

	//check the HTTP Status code (Expecting response OK)
	sf::Http::Response::Status status = response.getStatus();

	if (status == sf::Http::Response::Ok) {
		std::string responseStr = response.getBody();
		Score::parseResponseString(responseStr);
		return seglist;
		//std::cout << response.getBody();
	}
	else {
		std::cout << "An error occured while retrieving scores: " << status;
	}
}

void Score::parseResponseString(std::string str) {
	std::stringstream test(str);

	while (std::getline(test, segment, ';'))
	{
		seglist.push_back(segment);
	}
}

void Score::saveScore(std::string name, std::string score, std::string tijd) {

	//Call the file index.php on host jessy-visch.nl/ejento
	sf::Http::Request request("ejento/save.php", sf::Http::Request::Post);

	//Prepare parameter string
	std::ostringstream stream;
	stream << "naam=" << name << "&score=" << score << "&tijd=" << tijd;
	request.setBody(stream.str());

	//Sending the response and capturing the HTTP response
	sf::Http::Response response = http.sendRequest(request);

	//check the HTTP Status code (Expecting response OK)
	sf::Http::Response::Status status = response.getStatus();

	if (status == sf::Http::Response::Ok) {
		//std::string responseStr = response.getBody();
		//Score::parseResponseString(responseStr);
		std::cout << response.getBody();
	}
	else {
		std::cout << "An error occured while retrieving scores: " << status;
	}
}

void Score::draw(sf::RenderWindow &window) {

}