/*!
*   @author     Aydin Biber
*   @project    Themaopdracht 5, Ejento 148
*   @brief      The code to play audio
*/

#ifndef _AUDIO_HPP
#define _AUDIO_HPP

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>


class Audio {
public:
	/** \brief Plays music file
	* \details Plays the music file that is referenced in its parameter
	* \Param path path to the audio file
	* \Param volume volume which the music file will be played at.
	* \Param loop bool to set wether a music file should be looped or not.
	*/
	static void PlayMusic(std::string, float, bool);

	/** \brief Stops music file
	* \details Stops all music files that are currently playing
	*/
	static void StopMusic();

	/** \brief Plays a sound file
	* \details plays a short audio clip
	* \Param path path to the audio file
	* \Param volume volume which the music file will be played at.
	* \Param loop bool to set wether a music file should be looped or not.
	*/
	static void PlaySound(std::string, float, bool);

private:
	static sf::Music backgroundMusic;
	static sf::SoundBuffer buffer;
	static sf::Sound actionSound;
};

#endif