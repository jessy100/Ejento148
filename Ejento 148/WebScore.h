/*!
*   @author     Jessy Visch
*   @project    Themaopdracht 5, Ejento 148
*   @brief      The code for connecting to a remote http client to save and read scores.
*/

#ifndef _WEBSCORE_HPP
#define _WEBSCORE_HPP

#include <SFML\Graphics.hpp>
#include <string>
#include <http.h>
#include <SFML\Network.hpp>
#include "SFML\Network\Http.hpp"
 

class WebScore {
public:
	/** \brief Constructor of WebScore.
	* \details Instances the class
	*/
	WebScore();
	/** \brief Fetches score from online database
	* \details This function connects to remote http client and request score data.
	* Remote client return string of results.
	*/
	std::vector<std::string> WebScore::getScores();
	
	/** \brief Connects to remote client with a post request.
	* \details Builds a string of postdata and then calls the remote client.
	* \param name name of the player which was entered on the gameover screen.
	* \param score the amount of points the player has scored 
	* \param tijd the amount of time the player took to complete the level
	*/
	void WebScore::saveScore(std::string name, std::string score, std::string tijd);

	/** \brief Handles the string Webscore::getScores returns
	* \details Split the string that Webscore::getScores returns and pushes it into a vector
	* the result of this is that every vector element is a string containing a player name, a player score and a player time
	* \param str the string function getScores fetched from the remote client.
	*/
	void WebScore::parseResponseString(std::string str);

private:
	sf::Http http;
	std::string segment;
	std::vector<std::string> seglist;
};

#endif