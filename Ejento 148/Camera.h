/*!
*   @author     Jessy Visch
*   @project    Themaopdracht 5, Ejento 148
*   @brief      Super class for background and interactive tiles
*/

#ifndef _Camera_HPP
#define _Camera_HPP

#include "player.h"

class Camera
{
public:

	/** \brief Constructor of camera.
	* \details Creates Camera instance.
	* \Param Player reference to the player instance
	* \Param levelWidth The width of the level is used to make sure the camera doesnt go further then the actual level.
	*/
	Camera(Player & player, int levelWidth);

	/** \brief Resets the camera
	* \details Resets the camera view in case the level is reset or the gameoverscreen is called.
	* \Param window the sf::RenderWindow reference.
	*/
	void Reset(sf::RenderWindow &window);

	/** \brief Updates the Camera
	* \details Updates the camera with the players current position so it follows the player.
	* \after updating the camera position it sets the view.
	* \Param window the sf::RenderWindow reference.
	*/
	void update(sf::RenderWindow &window);

	/** \brief Returns the cameraPosition
	*/
	sf::Vector2f getPosition() { return cameraPosition; }

private:
	sf::View view;
	Player & player;
	sf::Vector2f screenDimensions;
	sf::Vector2f cameraPosition;
	int levelWidth;
};

#endif